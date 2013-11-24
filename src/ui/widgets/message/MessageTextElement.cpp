/*
 * MessageTextElement.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#include "MessageTextElement.h"
#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;

static const int TEXT_FONT_SIZE = 35;

MessageTextElement::MessageTextElement() {
	CONSTRUCT(L"MessageTextElement");
}

MessageTextElement::~MessageTextElement() {
	DESTRUCT(L"MessageTextElement");
//	delete pEnrichedText;
//	delete pFont;
}

result MessageTextElement::SetText(const String & text, bool emoji) {
	int width, height, textActualLen;
	result r = E_SUCCESS;
	Dimension textDim;
	Color textColor = Color::GetColor(COLOR_ID_WHITE);
	Bitmap *smile;
	String smilePath;

	if(emoji) {
		String currentSubstring;
		wchar_t currentChar;
		for(int i = 0; i < text.GetLength(); i++) {
			text.GetCharAt(i, currentChar);
			AppLog("SMILE: %d", currentChar);
			switch((int)currentChar) {
			case 169:
			case 174:
			case 8252:
			case 8265:
			case 8482:
			case 8505:
			case 8596:
			case 8597:
			case 8598:
			case 8599:
			case 8600:
			case 8601:
			case 8617:
			case 8618:
			case 8986:
			case 8987:
			case 9193:
			case 9194:
			case 9195:
			case 9196:
			case 9200:
			case 9203:
			case 9410:
			case 9642:
			case 9643:
			case 9654:
			case 9664:
			case 9723:
			case 9724:
			case 9725:
			case 9726:
			case 9728:
			case 9729:
			case 9742:
			case 9745:
			case 9748:
			case 9749:
			case 9757:
			case 9786:
			case 9800:
			case 9801:
			case 9802:
			case 9803:
			case 9804:
			case 9805:
			case 9806:
			case 9807:
			case 9808:
			case 9809:
			case 9810:
			case 9811:
			case 9824:
			case 9827:
			case 9829:
			case 9830:
			case 9832:
			case 9851:
			case 9855:
			case 9875:
			case 9888:
			case 9889:
			case 9898:
			case 9899:
			case 9917:
			case 9918:
			case 9924:
			case 9925:
			case 9934:
			case 9940:
			case 9962:
			case 9970:
			case 9971:
			case 9973:
			case 9978:
			case 9981:
			case 9986:
			case 9989:
			case 9992:
			case 9993:
			case 9994:
			case 9995:
			case 9996:
			case 9999:
			case 10002:
			case 10004:
			case 10006:
			case 10024:
			case 10035:
			case 10036:
			case 10052:
			case 10055:
			case 10060:
			case 10062:
			case 10067:
			case 10068:
			case 10069:
			case 10071:
			case 10084:
			case 10133:
			case 10134:
			case 10135:
			case 10145:
			case 10160:
			case 10175:
			case 10548:
			case 10549:
			case 11013:
			case 11014:
			case 11015:
			case 11035:
			case 11036:
			case 11088:
			case 11093:
			case 12336:
			case 12349:
			case 12951:
			case 12953:
			case 101603:
			case 114915:
			case 115939:
			case 116963:
			case 117987:
			case 119011:
			case 120035:
			case 121059:
			case 122083:
			case 123107:
			case 124131:
			case 126980:
			case 127183:
			case 127344:
			case 127345:
			case 127358:
			case 127359:
			case 127374:
			case 127377:
			case 127378:
			case 127379:
			case 127380:
			case 127381:
			case 127382:
			case 127383:
			case 127384:
			case 127385:
			case 127386:
			case 127489:
			case 127490:
			case 127514:
			case 127535:
			case 127538:
			case 127539:
			case 127540:
			case 127541:
			case 127542:
			case 127543:
			case 127544:
			case 127545:
			case 127546:
			case 127568:
			case 127569:
			case 127744:
			case 127745:
			case 127746:
			case 127747:
			case 127748:
			case 127749:
			case 127750:
			case 127751:
			case 127752:
			case 127753:
			case 127754:
			case 127755:
			case 127756:
			case 127757:
			case 127758:
			case 127759:
			case 127760:
			case 127761:
			case 127762:
			case 127763:
			case 127764:
			case 127765:
			case 127766:
			case 127767:
			case 127768:
			case 127769:
			case 127770:
			case 127771:
			case 127772:
			case 127773:
			case 127774:
			case 127775:
			case 127776:
			case 127792:
			case 127793:
			case 127794:
			case 127795:
			case 127796:
			case 127797:
			case 127799:
			case 127800:
			case 127801:
			case 127802:
			case 127803:
			case 127804:
			case 127805:
			case 127806:
			case 127807:
			case 127808:
			case 127809:
			case 127810:
			case 127811:
			case 127812:
			case 127813:
			case 127814:
			case 127815:
			case 127816:
			case 127817:
			case 127818:
			case 127819:
			case 127820:
			case 127821:
			case 127822:
			case 127823:
			case 127824:
			case 127825:
			case 127826:
			case 127827:
			case 127828:
			case 127829:
			case 127830:
			case 127831:
			case 127832:
			case 127833:
			case 127834:
			case 127835:
			case 127836:
			case 127837:
			case 127838:
			case 127839:
			case 127840:
			case 127841:
			case 127842:
			case 127843:
			case 127844:
			case 127845:
			case 127846:
			case 127847:
			case 127848:
			case 127849:
			case 127850:
			case 127851:
			case 127852:
			case 127853:
			case 127854:
			case 127855:
			case 127856:
			case 127857:
			case 127858:
			case 127859:
			case 127860:
			case 127861:
			case 127862:
			case 127863:
			case 127864:
			case 127865:
			case 127866:
			case 127867:
			case 127868:
			case 127872:
			case 127873:
			case 127874:
			case 127875:
			case 127876:
			case 127877:
			case 127878:
			case 127879:
			case 127880:
			case 127881:
			case 127882:
			case 127883:
			case 127884:
			case 127885:
			case 127886:
			case 127887:
			case 127888:
			case 127889:
			case 127890:
			case 127891:
			case 127904:
			case 127905:
			case 127906:
			case 127907:
			case 127908:
			case 127909:
			case 127910:
			case 127911:
			case 127912:
			case 127913:
			case 127914:
			case 127915:
			case 127916:
			case 127917:
			case 127918:
			case 127919:
			case 127920:
			case 127921:
			case 127922:
			case 127923:
			case 127924:
			case 127925:
			case 127926:
			case 127927:
			case 127928:
			case 127929:
			case 127930:
			case 127931:
			case 127932:
			case 127933:
			case 127934:
			case 127935:
			case 127936:
			case 127937:
			case 127938:
			case 127939:
			case 127940:
			case 127942:
			case 127943:
			case 127944:
			case 127945:
			case 127946:
			case 127968:
			case 127969:
			case 127970:
			case 127971:
			case 127972:
			case 127973:
			case 127974:
			case 127975:
			case 127976:
			case 127977:
			case 127978:
			case 127979:
			case 127980:
			case 127981:
			case 127982:
			case 127983:
			case 127984:
			case 128000:
			case 128001:
			case 128002:
			case 128003:
			case 128004:
			case 128005:
			case 128006:
			case 128007:
			case 128008:
			case 128009:
			case 128010:
			case 128011:
			case 128012:
			case 128013:
			case 128014:
			case 128015:
			case 128016:
			case 128017:
			case 128018:
			case 128019:
			case 128020:
			case 128021:
			case 128022:
			case 128023:
			case 128024:
			case 128025:
			case 128026:
			case 128027:
			case 128028:
			case 128029:
			case 128030:
			case 128031:
			case 128032:
			case 128033:
			case 128034:
			case 128035:
			case 128036:
			case 128037:
			case 128038:
			case 128039:
			case 128040:
			case 128041:
			case 128042:
			case 128043:
			case 128044:
			case 128045:
			case 128046:
			case 128047:
			case 128048:
			case 128049:
			case 128050:
			case 128051:
			case 128052:
			case 128053:
			case 128054:
			case 128055:
			case 128056:
			case 128057:
			case 128058:
			case 128059:
			case 128060:
			case 128061:
			case 128062:
			case 128064:
			case 128066:
			case 128067:
			case 128068:
			case 128069:
			case 128070:
			case 128071:
			case 128072:
			case 128073:
			case 128074:
			case 128075:
			case 128076:
			case 128077:
			case 128078:
			case 128079:
			case 128080:
			case 128081:
			case 128082:
			case 128083:
			case 128084:
			case 128085:
			case 128086:
			case 128087:
			case 128088:
			case 128089:
			case 128090:
			case 128091:
			case 128092:
			case 128093:
			case 128094:
			case 128095:
			case 128096:
			case 128097:
			case 128098:
			case 128099:
			case 128100:
			case 128101:
			case 128102:
			case 128103:
			case 128104:
			case 128105:
			case 128106:
			case 128107:
			case 128108:
			case 128109:
			case 128110:
			case 128111:
			case 128112:
			case 128113:
			case 128114:
			case 128115:
			case 128116:
			case 128117:
			case 128118:
			case 128119:
			case 128120:
			case 128121:
			case 128122:
			case 128123:
			case 128124:
			case 128125:
			case 128126:
			case 128127:
			case 128128:
			case 128129:
			case 128130:
			case 128131:
			case 128132:
			case 128133:
			case 128134:
			case 128135:
			case 128136:
			case 128137:
			case 128138:
			case 128139:
			case 128140:
			case 128141:
			case 128142:
			case 128143:
			case 128144:
			case 128145:
			case 128146:
			case 128147:
			case 128148:
			case 128149:
			case 128150:
			case 128151:
			case 128152:
			case 128153:
			case 128154:
			case 128155:
			case 128156:
			case 128157:
			case 128158:
			case 128159:
			case 128160:
			case 128161:
			case 128162:
			case 128163:
			case 128164:
			case 128165:
			case 128166:
			case 128167:
			case 128168:
			case 128169:
			case 128170:
			case 128171:
			case 128172:
			case 128173:
			case 128174:
			case 128175:
			case 128176:
			case 128177:
			case 128178:
			case 128179:
			case 128180:
			case 128181:
			case 128182:
			case 128183:
			case 128184:
			case 128185:
			case 128186:
			case 128187:
			case 128188:
			case 128189:
			case 128190:
			case 128191:
			case 128192:
			case 128193:
			case 128194:
			case 128195:
			case 128196:
			case 128197:
			case 128198:
			case 128199:
			case 128200:
			case 128201:
			case 128202:
			case 128203:
			case 128204:
			case 128205:
			case 128206:
			case 128207:
			case 128208:
			case 128209:
			case 128210:
			case 128211:
			case 128212:
			case 128213:
			case 128214:
			case 128215:
			case 128216:
			case 128217:
			case 128218:
			case 128219:
			case 128220:
			case 128221:
			case 128222:
			case 128223:
			case 128224:
			case 128225:
			case 128226:
			case 128227:
			case 128228:
			case 128229:
			case 128230:
			case 128231:
			case 128232:
			case 128233:
			case 128234:
			case 128235:
			case 128236:
			case 128237:
			case 128238:
			case 128239:
			case 128240:
			case 128241:
			case 128242:
			case 128243:
			case 128244:
			case 128245:
			case 128246:
			case 128247:
			case 128249:
			case 128250:
			case 128251:
			case 128252:
			case 128256:
			case 128257:
			case 128258:
			case 128259:
			case 128260:
			case 128261:
			case 128262:
			case 128263:
			case 128264:
			case 128265:
			case 128266:
			case 128267:
			case 128268:
			case 128269:
			case 128270:
			case 128271:
			case 128272:
			case 128273:
			case 128274:
			case 128275:
			case 128276:
			case 128277:
			case 128278:
			case 128279:
			case 128280:
			case 128281:
			case 128282:
			case 128283:
			case 128284:
			case 128285:
			case 128286:
			case 128287:
			case 128288:
			case 128289:
			case 128290:
			case 128291:
			case 128292:
			case 128293:
			case 128294:
			case 128295:
			case 128296:
			case 128297:
			case 128298:
			case 128299:
			case 128300:
			case 128301:
			case 128302:
			case 128303:
			case 128304:
			case 128305:
			case 128306:
			case 128307:
			case 128308:
			case 128309:
			case 128310:
			case 128311:
			case 128312:
			case 128313:
			case 128314:
			case 128315:
			case 128316:
			case 128317:
			case 128336:
			case 128337:
			case 128338:
			case 128339:
			case 128340:
			case 128341:
			case 128342:
			case 128343:
			case 128344:
			case 128345:
			case 128346:
			case 128347:
			case 128348:
			case 128349:
			case 128350:
			case 128351:
			case 128352:
			case 128353:
			case 128354:
			case 128355:
			case 128356:
			case 128357:
			case 128358:
			case 128359:
			case 128507:
			case 128508:
			case 128509:
			case 128510:
			case 128511:
			case 128512:
			case 128513:
			case 128514:
			case 128515:
			case 128516:
			case 128517:
			case 128518:
			case 128519:
			case 128520:
			case 128521:
			case 128522:
			case 128523:
			case 128524:
			case 128525:
			case 128526:
			case 128527:
			case 128528:
			case 128529:
			case 128530:
			case 128531:
			case 128532:
			case 128533:
			case 128534:
			case 128535:
			case 128536:
			case 128537:
			case 128538:
			case 128539:
			case 128540:
			case 128541:
			case 128542:
			case 128543:
			case 128544:
			case 128545:
			case 128546:
			case 128547:
			case 128548:
			case 128549:
			case 128550:
			case 128551:
			case 128552:
			case 128553:
			case 128554:
			case 128555:
			case 128556:
			case 128557:
			case 128558:
			case 128559:
			case 128560:
			case 128561:
			case 128562:
			case 128563:
			case 128564:
			case 128565:
			case 128566:
			case 128567:
			case 128568:
			case 128569:
			case 128570:
			case 128571:
			case 128572:
			case 128573:
			case 128574:
			case 128575:
			case 128576:
			case 128581:
			case 128582:
			case 128583:
			case 128584:
			case 128585:
			case 128586:
			case 128587:
			case 128588:
			case 128589:
			case 128590:
			case 128591:
			case 128640:
			case 128641:
			case 128642:
			case 128643:
			case 128644:
			case 128645:
			case 128646:
			case 128647:
			case 128648:
			case 128649:
			case 128650:
			case 128651:
			case 128652:
			case 128653:
			case 128654:
			case 128655:
			case 128656:
			case 128657:
			case 128658:
			case 128659:
			case 128660:
			case 128661:
			case 128662:
			case 128663:
			case 128664:
			case 128665:
			case 128666:
			case 128667:
			case 128668:
			case 128669:
			case 128670:
			case 128671:
			case 128672:
			case 128673:
			case 128674:
			case 128675:
			case 128676:
			case 128677:
			case 128678:
			case 128679:
			case 128680:
			case 128681:
			case 128682:
			case 128683:
			case 128684:
			case 128685:
			case 128686:
			case 128687:
			case 128688:
			case 128689:
			case 128690:
			case 128691:
			case 128692:
			case 128693:
			case 128694:
			case 128695:
			case 128696:
			case 128697:
			case 128698:
			case 128699:
			case 128700:
			case 128701:
			case 128702:
			case 128703:
			case 128704:
			case 128705:
			case 128706:
			case 128707:
			case 128708:
			case 128709:


				AppLog("SMILE item %d", (int)currentChar);
				if(!currentSubstring.IsEmpty()) {
					TextElement *pTextElement = new TextElement();
					r = pTextElement->Construct(currentSubstring);
					TryCatch(r == E_SUCCESS, , "Failed TextElement");
					r = pTextElement->SetTextColor(textColor);
					TryCatch(r == E_SUCCESS, , "Failed SetTextColor");
					r = pTextElement->SetFont(*pFont);
					TryCatch(r == E_SUCCESS, , "Failed SetFont");
					r = pEnrichedText->Add(*pTextElement);
					TryCatch(r == E_SUCCESS, , "Failed Add textElement");
					currentSubstring = String();
				}

				smilePath = String(L"emoji/");
				smilePath.Append((int)currentChar);
				smilePath.Append(L".png");
				AppLog("SMILE path %ls", smilePath.GetPointer());
				smile = VKUApp::GetInstance()->GetAppResource()->GetBitmapN(smilePath);
				if(smile != null) {
					AppLog("SMILE successfull load smile, size: %dx%d", smile->GetWidth(), smile->GetHeight());
					r = pEnrichedText->Add(*smile);
					delete smile;
					TryCatch(r == E_SUCCESS, , "Failed Add textElement");
				} else {
					AppLog("SMILE failed to load smile: %s", GetErrorMessage(GetLastResult()));
				}

				break;
			default:
				currentSubstring.Append(currentChar);
				break;
			}
		}

		if(!currentSubstring.IsEmpty()) {
			TextElement *pTextElement = new TextElement();
			r = pTextElement->Construct(currentSubstring);
			TryCatch(r == E_SUCCESS, , "Failed TextElement");
			r = pTextElement->SetTextColor(textColor);
			TryCatch(r == E_SUCCESS, , "Failed SetTextColor");
			r = pTextElement->SetFont(*pFont);
			TryCatch(r == E_SUCCESS, , "Failed SetFont");
			r = pEnrichedText->Add(*pTextElement);
			TryCatch(r == E_SUCCESS, , "Failed Add textElement");
			currentSubstring = String();
		}

	} else {
		TextElement *pTextElement = new TextElement();
		r = pTextElement->Construct(text);
		TryCatch(r == E_SUCCESS, , "Failed TextElement");
		r = pTextElement->SetTextColor(textColor);
		TryCatch(r == E_SUCCESS, , "Failed SetTextColor");
		r = pTextElement->SetFont(*pFont);
		TryCatch(r == E_SUCCESS, , "Failed SetFont");
		r = pEnrichedText->Add(*pTextElement);
		TryCatch(r == E_SUCCESS, , "Failed Add textElement");
	}

	height = pEnrichedText->GetTotalLineHeight();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed pEnrichedText->GetTotalLineHeight");

	r = pEnrichedText->GetTextExtent(0, text.GetLength(), textDim, textActualLen);
	TryCatch(r == E_SUCCESS, , "Failed GetTextExtent");

	if (pEnrichedText->GetTotalLineCount() > 1) {
		textDim.width = GetSize().width;
	}

	width = GetSize().width < textDim.width ? GetSize().width : textDim.width;
	AppLog("MessageTextElement Size: %d x %d", width, height);

	r = SetSize(width, height);
	TryCatch(r == E_SUCCESS, , "Failed SetSize");

	return r;

CATCH:
	AppLogException("MessageTextElement::SetText is failed. %s", GetErrorMessage(r));
	return r;
}

result MessageTextElement::Construct(const Rectangle & rect) {
	result r = E_SUCCESS;

	r = Panel::Construct(rect);
	TryCatch(r == E_SUCCESS, , "Failed Panel::Construct");

	pFont = new Font();
	r = pFont->Construct(FONT_STYLE_PLAIN, TEXT_FONT_SIZE);
	TryCatch(r == E_SUCCESS, , "Failed pFont->Construct");

	pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(rect.width, rect.height));
	TryCatch(r == E_SUCCESS, , "Failed pEnrichedText->Construct");

	return r;

CATCH:
	AppLogException("MessageTextElement::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

result MessageTextElement::OnDraw(void) {
	result r = E_SUCCESS;
	Canvas * pCanvas = GetCanvasN();

	r = pCanvas->DrawText(Point(0, 0), *pEnrichedText);
	TryCatch(r == E_SUCCESS, , "Failed DrawText");

	delete pCanvas;
	return r;

	CATCH:
	    AppLogException("MessageTextElement::OnDraw is failed. %s", GetErrorMessage(r));
	    return r;
}
