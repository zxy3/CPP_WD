// ///使用tinyXml2解析RSS文件，并生成一个网页库pagelib.dat

// #include "tinyxml2.h"

// #include <cerrno>
// #include <cstdlib>
// #include <cstring>
// #include <ctime>

// using namespace tinyxml2;
// using namespace std;
// int gPass = 0;
// int gFail = 0;

// bool XMLTest(const char *testString, const char *expected, const char *found, bool echo = true, bool extraNL = false)
// {
//     bool pass;
//     if (!expected && !found)
//         pass = true;
//     else if (!expected || !found)
//         pass = false;
//     else
//         pass = !strcmp(expected, found);
//     if (pass)
//         printf("[pass]");
//     else
//         printf("[fail]");

//     if (!echo)
//     {
//         printf(" %s\n", testString);
//     }
//     else
//     {
//         if (extraNL)
//         {
//             printf(" %s\n", testString);
//             printf("%s\n", expected);
//             printf("%s\n", found);
//         }
//         else
//         {
//             printf(" %s [%s][%s]\n", testString, expected, found);
//         }
//     }

//     if (pass)
//         ++gPass;
//     else
//         ++gFail;
//     return pass;
// }

// bool XMLTest(const char *testString, XMLError expected, XMLError found, bool echo = true, bool extraNL = false)
// {
//     return XMLTest(testString, XMLDocument::ErrorIDToName(expected), XMLDocument::ErrorIDToName(found), echo, extraNL);
// }

// bool XMLTest(const char *testString, bool expected, bool found, bool echo = true, bool extraNL = false)
// {
//     return XMLTest(testString, expected ? "true" : "false", found ? "true" : "false", echo, extraNL);
// }

// template <class T>
// bool XMLTest(const char *testString, T expected, T found, bool echo = true)
// {
//     bool pass = (expected == found);
//     if (pass)
//         printf("[pass]");
//     else
//         printf("[fail]");

//     if (!echo)
//         printf(" %s\n", testString);
//     else
//     {
//         char expectedAsString[64];
//         XMLUtil::ToStr(expected, expectedAsString, sizeof(expectedAsString));

//         char foundAsString[64];
//         XMLUtil::ToStr(found, foundAsString, sizeof(foundAsString));

//         printf(" %s [%s][%s]\n", testString, expectedAsString, foundAsString);
//     }

//     if (pass)
//         ++gPass;
//     else
//         ++gFail;
//     return pass;
// }

// //加载XML文件
// int test0()
// {
//     XMLDocument doc;
//     doc.LoadFile("coolshell.xml");

//     return doc.ErrorID();
// }
// //检查字符串<element/>
// int example_2()
// {
//     static const char *xml = "<element/>";
//     XMLDocument doc;
//     doc.Parse(xml);

//     return doc.ErrorID();
// }

// // 获取xml文件中的title节点内部的值
// int test3()
// {
//     // XMLDocument doc;
//     // doc.LoadFile("coolshell.xml");
//     static const char *xml =
//         "<?xml version=\"1.0\"?>"
//         "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
//         "<PLAY>"
//         "<TITLE> 我是标题-->title </TITLE>"
//         "</PLAY>";

//     XMLDocument doc;
//     doc.Parse(xml);
//     // 根节点的孩子节点的值
//     XMLElement *titleElement = doc.FirstChildElement("PLAY")->FirstChildElement("TITLE");
//     const char *title = titleElement->GetText();
//     printf("Name of play (1): %s\n", title);
//     // 根节点的第一个孩子的值
//     XMLText *textNode = titleElement->FirstChild()->ToText();
//     title = textNode->Value();
//     printf("Name of play (2): %s\n", title);

//     return doc.ErrorID();
// }

// // 提取同一个属性的东西
// bool test4()
// {
//     static const char *xml =
//         "<information>"
//         "	<attributeApproach v='2' />"
//         "	<textApproach>"
//         "		<v>2</v>"
//         "	</textApproach>"
//         "</information>";

//     XMLDocument doc;
//     doc.Parse(xml);

//     int v0 = 0;
//     int v1 = 0;

//     XMLElement *attributeApproachElement = doc.FirstChildElement()->FirstChildElement("attributeApproach");
//     attributeApproachElement->QueryIntAttribute("v", &v0);

//     XMLElement *textApproachElement = doc.FirstChildElement()->FirstChildElement("textApproach");
//     textApproachElement->FirstChildElement("v")->QueryIntText(&v1);

//     printf("Both values are the same: %d and %d\n", v0, v1);

//     return !doc.Error() && (v0 == v1);
// }

// //测试代码
// int main(void)
// {
//     // 参考xmltest(我也不知道这是什么东西)
//     {
//         TIXMLASSERT(true);
//     }

//     // XMLDocument *doc = new XMLDocument();
//     // clock_t startTime = clock();
//     // doc->LoadFile("coolshell.xml");
//     // clock_t loadTime = clock();
//     // int errorID = doc->ErrorID();
//     // delete doc;
//     // doc = 0;
//     // clock_t deleteTime = clock();

//     // printf("Test file '%s' loaded. ErrorID=%d\n", "coolshell.xml", errorID);
//     // if (!errorID)
//     // {
//     //     // 这是什么东西
//     //     printf("Load time=%u\n", (unsigned)(loadTime - startTime));
//     //     printf("Delete time=%u\n", (unsigned)(deleteTime - loadTime));
//     //     printf("Total time=%u\n", (unsigned)(deleteTime - startTime));
//     // }
//     // exit(0);

//     FILE *fp = fopen("coolshell.xml", "r");
//     if (!fp)
//     {
//         printf("Error opening test file 'coolshell.xml'.\n"
//                "Is your working directory the same as where \n"
//                "the test.cpp and coolshell.xml file are?\n\n"
// #if defined(_MSC_VER)
//                "In windows Visual Studio you may need to set\n"
//                "Properties->Debugging->Working Directory to '..'\n"
// #endif
//         );
//         exit(1);
//     }
//     else
//     {
//         // std::cout << "xml打开成功" << endl;
//         printf("xml打开成功\n");
//     }
//     fclose(fp);

//     // {
//     //     static const char *test[] = {"<element />",
//     //                                  "<element></element>",
//     //                                  "<element><subelement/></element>",
//     //                                  "<element><subelement></subelement></element>",
//     //                                  "<element><subelement><subsub/></subelement></element>",
//     //                                  "<!--comment beside elements--><element><subelement></subelement></element>",
//     //                                  "<!--comment beside elements, this time with spaces-->  \n <element>  <subelement> \n </subelement> </element>",
//     //                                  "<element attrib1='foo' attrib2=\"bar\" ></element>",
//     //                                  "<element attrib1='foo' attrib2=\"bar\" ><subelement attrib3='yeehaa' /></element>",
//     //                                  "<element>Text inside element.</element>",
//     //                                  "<element><b></b></element>",
//     //                                  "<element>Text inside and <b>bolded</b> in the element.</element>",
//     //                                  "<outer><element>Text inside and <b>bolded</b> in the element.</element></outer>",
//     //                                  "<element>This &amp; That.</element>",
//     //                                  "<element attrib='This&lt;That' />",
//     //                                  0};

//     //     for (int i = 0; test[i]; ++i)
//     //     {
//     //         XMLDocument doc;
//     //         doc.Parse(test[i]);
//     //         // XMLTest("Element test", false, doc.Error());
//     //         doc.Print();
//     //         printf("----------------------------------------------\n");
//     //     }
//     // }

//     // 一个打印的函数
//     // {
//     //     static const char *test = "<!--hello world\n"
//     //                               "          line 2\r"
//     //                               "          line 3\r\n"
//     //                               "          line 4\n\r"
//     //                               "          line 5\r-->";

//     //     XMLDocument doc;
//     //     doc.Parse(test);
//     //     // XMLTest( "Hello world declaration", false, doc.Error() );
//     //     doc.Print();
//     // }

//     // 为下一个代码做准备
//     // {
//     //     // This test is pre-test for the next one
//     //     // (where Element1 is inserted "after itself".
//     //     // This code didn't use to crash.
//     //     XMLDocument doc;
//     //     XMLElement *element1 = doc.NewElement("Element1");
//     //     XMLElement *element2 = doc.NewElement("Element2");
//     //     doc.InsertEndChild(element1);
//     //     doc.InsertEndChild(element2);
//     //     doc.InsertAfterChild(element2, element2);
//     //     doc.InsertAfterChild(element2, element2);
//     // }

//     // {
//     // 	XMLDocument doc;
//     // 	XMLElement* element1 = doc.NewElement("Element1");
//     // 	XMLElement* element2 = doc.NewElement("Element2");
//     // 	doc.InsertEndChild(element1);
//     // 	doc.InsertEndChild(element2);
//     // 	// This insertion "after itself"
//     // 	// used to cause invalid memory access and crash
//     // 	doc.InsertAfterChild(element1, element1);
//     // 	doc.InsertAfterChild(element1, element1);
//     // 	doc.InsertAfterChild(element2, element2);
//     // 	doc.InsertAfterChild(element2, element2);
//     // }

//     // 增加节点
//     // {
//     // 	static const char* test = "<element>Text before.</element>";
//     // 	XMLDocument doc;
//     // 	doc.Parse( test );
//     // 	// XMLTest( "Element text before", false, doc.Error() );
//     // 	XMLElement* root = doc.FirstChildElement();
//     // 	XMLElement* newElement = doc.NewElement( "Subelement" );
//     // 	root->InsertEndChild( newElement );
//     // 	doc.Print();
//     // }

//     // {
//     // 	XMLDocument* doc = new XMLDocument();
//     // 	static const char* test = "<element><sub/></element>";
//     //     // 从字符串解析XML
//     // 	doc->Parse( test );
//     // 	// XMLTest( "Element with sub element", false, doc->Error() );
//     // 	delete doc;
//     // }
//     // // 创建新节点
//     // {
//     //     // Test: Programmatic DOM nodes insertion return values
//     //     XMLDocument doc;

//     //     XMLNode *first = doc.NewElement("firstElement");
//     //     // XMLTest( "New element", true, first != 0 );
//     //     XMLNode *firstAfterInsertion = doc.InsertFirstChild(first);
//     //     // XMLTest( "New element inserted first", true, firstAfterInsertion == first );

//     //     XMLNode *last = doc.NewElement("lastElement");
//     //     // XMLTest( "New element", true, last != 0 );
//     //     XMLNode *lastAfterInsertion = doc.InsertEndChild(last);
//     //     // XMLTest( "New element inserted last", true, lastAfterInsertion == last );

//     //     XMLNode *middle = doc.NewElement("middleElement");
//     //     // XMLTest( "New element", true, middle != 0 );
//     //     XMLNode *middleAfterInsertion = doc.InsertAfterChild(first, middle);
//     //     // XMLTest( "New element inserted middle", true, middleAfterInsertion == middle );
//     //     doc.Print();
//     // }

//     // // 创建节点
//     // {
//     //     // Test: Programmatic DOM
//     //     // Build:
//     //     //		<element>
//     //     //			<!--comment-->
//     //     //			<sub attrib="1" />
//     //     //			<sub attrib="2" />
//     //     //			<sub attrib="3" >& Text!</sub>
//     //     //		<element>

//     //     XMLDocument *doc = new XMLDocument();
//     //     XMLNode *element = doc->InsertEndChild(doc->NewElement("element"));

//     //     XMLElement *sub[3] = {doc->NewElement("sub"), doc->NewElement("sub"), doc->NewElement("sub")};
//     //     for (int i = 0; i < 3; ++i)
//     //     {
//     //         sub[i]->SetAttribute("attrib", i);
//     //     }
//     //     element->InsertEndChild(sub[2]);

//     //     const int dummyInitialValue = 1000;
//     //     int dummyValue = dummyInitialValue;

//     //     XMLNode *comment = element->InsertFirstChild(doc->NewComment("comment"));
//     //     comment->SetUserData(&dummyValue);
//     //     element->InsertAfterChild(comment, sub[0]);
//     //     element->InsertAfterChild(sub[0], sub[1]);
//     //     sub[2]->InsertFirstChild(doc->NewText("& Text!"));
//     //     doc->Print();
//     //     // XMLTest( "Programmatic DOM", "comment", doc->FirstChildElement( "element" )->FirstChild()->Value() );
//     //     // XMLTest( "Programmatic DOM", "0", doc->FirstChildElement( "element" )->FirstChildElement()->Attribute( "attrib" ) );
//     //     // XMLTest( "Programmatic DOM", 2, doc->FirstChildElement()->LastChildElement( "sub" )->IntAttribute( "attrib" ) );
//     //     // XMLTest( "Programmatic DOM", "& Text!",
//     //     // doc->FirstChildElement()->LastChildElement( "sub" )->FirstChild()->ToText()->Value() );
//     //     // XMLTest("User data - pointer", true, &dummyValue == comment->GetUserData(), false);
//     //     // XMLTest("User data - value behind pointer", dummyInitialValue, dummyValue, false);

//     //     // And now deletion:
//     //     element->DeleteChild(sub[2]);
//     //     doc->DeleteNode(comment);

//     //     element->FirstChildElement()->SetAttribute("attrib", true);
//     //     element->LastChildElement()->DeleteAttribute("attrib");

//     //     // XMLTest( "Programmatic DOM", true, doc->FirstChildElement()->FirstChildElement()->BoolAttribute( "attrib" ) );
//     //     const int defaultIntValue = 10;
//     //     const int replacementIntValue = 20;
//     //     int value1 = defaultIntValue;
//     //     int value2 = doc->FirstChildElement()->LastChildElement()->IntAttribute("attrib", replacementIntValue);
//     //     XMLError result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute("attrib", &value1);
//     //     // XMLTest( "Programmatic DOM", XML_NO_ATTRIBUTE, result );
//     //     // XMLTest( "Programmatic DOM", defaultIntValue, value1 );
//     //     // XMLTest( "Programmatic DOM", replacementIntValue, value2 );

//     //     doc->Print();

//     //     {
//     //         XMLPrinter streamer;
//     //         doc->Print(&streamer);
//     //         printf("%s", streamer.CStr());
//     //     }
//     //     {
//     //         XMLPrinter streamer(0, true);
//     //         doc->Print(&streamer);
//     //         // XMLTest( "Compact mode", "<element><sub attrib=\"true\"/><sub/></element>", streamer.CStr(), false );
//     //     }
//     //     doc->SaveFile("pretty.xml");
//     //     // XMLTest( "Save pretty.xml", false, doc->Error() );
//     //     doc->SaveFile("compact.xml", true);
//     //     // XMLTest( "Save compact.xml", false, doc->Error() );
//     //     doc->Print();
//     //     delete doc;
//     // }

//     {
//         // Test: Dream
//         // XML1 : 1,187,569 bytes	in 31,209 allocations
//         // XML2 :   469,073	bytes	in    323 allocations
//         //int newStart = gNew;
//         XMLDocument doc;
//         doc.LoadFile("coolshell.xml");
//         XMLTest("Load dream.xml", false, doc.Error());

//         doc.SaveFile("./out/coolsheelout.xml");
//         XMLTest("Save dreamout.xml", false, doc.Error());
//         doc.PrintError();

//         XMLTest("Dream", "xml version=\"1.0\"",
//                 doc.FirstChild()->ToDeclaration()->Value());
//         XMLTest("Dream", true, doc.FirstChild()->NextSibling()->ToUnknown() != 0);
//         XMLTest("Dream", "DOCTYPE PLAY SYSTEM \"play.dtd\"",
//                 doc.FirstChild()->NextSibling()->ToUnknown()->Value());
//         XMLTest("Dream", "And Robin shall restore amends.",
//                 doc.LastChild()->LastChild()->LastChild()->LastChild()->LastChildElement()->GetText());
//         XMLTest("Dream", "And Robin shall restore amends.",
//                 doc.LastChild()->LastChild()->LastChild()->LastChild()->LastChildElement()->GetText());

//         XMLDocument doc2;
//         doc2.LoadFile("./out/coolshell.xml");
//         XMLTest("Load coolshellout.xml", false, doc2.Error());
//         XMLTest("Dream-out", "xml version=\"1.0\"",
//                 doc2.FirstChild()->ToDeclaration()->Value());
//         XMLTest("Dream-out", true, doc2.FirstChild()->NextSibling()->ToUnknown() != 0);
//         XMLTest("Dream-out", "DOCTYPE PLAY SYSTEM \"play.dtd\"",
//                 doc2.FirstChild()->NextSibling()->ToUnknown()->Value());
//         XMLTest("Dream-out", "And Robin shall restore amends.",
//                 doc2.LastChild()->LastChild()->LastChild()->LastChild()->LastChildElement()->GetText());

//         //gNewTotal = gNew - newStart;
//     }
//     // test0();
//     // test1();
//     // test2();
//     // test3();
//     // test4();
//     return 0;
// }
