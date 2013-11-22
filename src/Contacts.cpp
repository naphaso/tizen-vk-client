/*
 * Contacts.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: wolong
 */

#include "Contacts.h"
#include "VKU.h"
#include "JsonParseUtils.h"
#include "VKUApi.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Social;
using namespace Tizen::Io;
using namespace Tizen::Web::Json;

Contacts::Contacts() {

}

Contacts::~Contacts() {

}

result Contacts::Sync() {
	result r = E_SUCCESS;

	//IList *accounts = AccountAccessor::GetInstance()->GetAccountsByAccountProviderN(VKUApp::GetInstance()->GetAppId());
	//TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "failed to get accounts list");


	if(IsConfigExists()) {
		ReadConfig();
	} else {
		InitConfig();
		WriteConfig();
	}

	VKUApi::GetInstance().CreateRequest("friends.get", this)->Put(L"fields", L"contacts,photo_100")->Submit(REQUEST_SYNC_CONTACTS);

	return r;
	CATCH:
	AppLogException("sync failed: %s", GetErrorMessage(r));
	return r;
}

bool Contacts::IsConfigExists() {
	String configPath(VKUApp::GetInstance()->GetAppDataPath() + L"contacts.ini");
	return File::IsFileExist(configPath);
}

void Contacts::ReadConfig() {
	String configPath(VKUApp::GetInstance()->GetAppDataPath() + L"contacts.ini");
	String contactsSection(L"contacts");

	Registry registry;
	registry.Construct(configPath, false);
	registry.GetValue(contactsSection, "account", accountId);
	registry.GetValue(contactsSection, "addressbook", addressbookId);
}

void Contacts::WriteConfig() {
	String configPath(VKUApp::GetInstance()->GetAppDataPath() + L"contacts.ini");
	String contactsSection(L"contacts");

	Registry registry;
	registry.Construct(configPath, true);
	registry.AddSection(contactsSection);
	registry.AddValue(contactsSection, L"account", accountId);
	registry.AddValue(contactsSection, L"addressbook", addressbookId);
	registry.Flush();
}

void Contacts::InitConfig() {
	result r;
	AddressbookManager *addressbookManager = AddressbookManager::GetInstance();
	Addressbook *addressbook;
	Account account("VK");
	account.SetExtendedData(L"ContactsSync", L"enable");
	account.SetExtendedData("CalendarSync", L"disable");

	AccountManager *accountManager = AccountManager::GetInstance();
	r = accountManager->AddAccount(account);
	TryCatch(r == E_SUCCESS,, "Failed to add account");

	accountId = account.GetId();

	AppLog("successfully created account with id %d", accountId);

	addressbook = addressbookManager->CreateAddressbookN(accountId, L"Friends");

	addressbookId = addressbook->GetId();

	AppLog("successfully create addressbook with id %d", addressbookId);

	delete addressbook;
	return;
	CATCH:
	AppLogException("failed to init contacts config: %s", GetErrorMessage(r));
	return;
}

void Contacts::OnResponseN(JsonObject *response) {
	result r;
	JsonObject *data;
	JsonArray *friends;
	AddressbookManager *addressbookManager = AddressbookManager::GetInstance();
	IList *contacts = addressbookManager->GetAllContactsN();


	r = JsonParseUtils::GetObject(response, L"response", data);
	TryCatch(r == E_SUCCESS, , "failed to get response from response");

	r = JsonParseUtils::GetArray(data, L"items", friends);
	TryCatch(r == E_SUCCESS, , "failed to get items from response");

	for(int i = 0; i < friends->GetCount(); i++) {
		JsonObject *someFriend;
		int id;
		String firstName;
		String lastName;
		String mobilePhone;
		String photoUrl;
		String pageUrl(L"http://vk.com/id");
		String thumbPath;
		ContactAppLaunchData appLaunchData;

		r = JsonParseUtils::GetObject(friends, i, someFriend);
		TryCatch(r == E_SUCCESS, , "failed to get friend %d from response", i);

		r = JsonParseUtils::GetString(*someFriend, L"first_name", firstName);
		TryCatch(r == E_SUCCESS, , "failed to get first name from friend");

		r = JsonParseUtils::GetString(*someFriend, L"last_name", lastName);
		TryCatch(r == E_SUCCESS, , "failed to get last name from friend");

		r = JsonParseUtils::GetString(*someFriend, L"photo_100", photoUrl);
		TryCatch(r == E_SUCCESS, , "failed to get photo url from friend");

		r = JsonParseUtils::GetString(*someFriend, L"mobile_phone", mobilePhone);
		//r = JsonParseUtils::GetString(someFriend, L"mobile_phone", mobilePhone);
		//TryCatch(r == E_SUCCESS, , "failed to get friend from response");
		r = JsonParseUtils::GetInteger(*someFriend, L"id", id);
		TryCatch(r == E_SUCCESS, , "failed to get id from friend");

		AppLog("friend id %d: %ls %ls", id, firstName.GetPointer(), lastName.GetPointer());

		pageUrl.Append(id);

		Contact *contact = GetExistingContact(contacts, pageUrl);
		if(contact == null) {
			contact = new Contact();
			contact->SetValue(CONTACT_PROPERTY_ID_FIRST_NAME, firstName);
			contact->SetValue(CONTACT_PROPERTY_ID_LAST_NAME, lastName);

			contact->AddUrl(Url(URL_TYPE_PERSONAL, pageUrl));

			appLaunchData.SetAppId(VKUApp::GetInstance()->GetAppId());
			appLaunchData.SetDisplayText(L"Open chat");
			appLaunchData.SetOperationId(L"OPEN_DIALOG");
			appLaunchData.SetUri(pageUrl);
			contact->AddContactAppLaunchData(appLaunchData);

			PhoneNumber phoneNumber(PHONENUMBER_TYPE_MOBILE, mobilePhone);
			contact->AddPhoneNumber(phoneNumber);

			thumbPath = CacheFileFromUrl(photoUrl);
			if(File::IsFileExist(thumbPath)) {
				contact->SetThumbnail(thumbPath);
			}

			r = addressbookManager->AddContact(*contact, addressbookId);
			TryCatch(r == E_SUCCESS, , "failed to add contact to addressbook");
			delete contact;
		} else {
			contact->SetValue(CONTACT_PROPERTY_ID_FIRST_NAME, firstName);
			contact->SetValue(CONTACT_PROPERTY_ID_LAST_NAME, lastName);

			thumbPath = CacheFileFromUrl(photoUrl);
			if(File::IsFileExist(thumbPath)) {
				contact->SetThumbnail(thumbPath);
			}

			PhoneNumber phoneNumber(PHONENUMBER_TYPE_MOBILE, mobilePhone);
			contact->SetPhoneNumberAt(0, phoneNumber);

			r = addressbookManager->UpdateContact(*contact);
			TryCatch(r == E_SUCCESS, , "failed to update contact in addressbook");
		}
	}

	delete contacts;
	return;
	CATCH:
	AppLogException("failed to get friends: %s", GetErrorMessage(r));
	delete contacts;
	return;
}

Contact *Contacts::GetExistingContact(IList *contacts, const String &pageUrl) {
	for(int i = 0; i < contacts->GetCount(); i++) {
		Contact *contact = static_cast<Contact *>(contacts->GetAt(i));
		IList *urls = contact->GetValuesN(CONTACT_MPROPERTY_ID_URLS);
		for(int j = 0; j < urls->GetCount(); j++) {
			Url *url = static_cast<Url*>(urls->GetAt(j));
			if(url->GetUrl().CompareTo(pageUrl) == 0) {
				delete urls;
				return contact;
			}
		}
		delete urls;
	}

	return null;
}
