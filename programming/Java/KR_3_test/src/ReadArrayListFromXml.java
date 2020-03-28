import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class ReadArrayListFromXml {
    public static void read(File file, ArrayList<Drink> arrayList) throws ParserConfigurationException, IOException, SAXException {
        arrayList.clear();
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(file);
        NodeList nodeList = document.getElementsByTagName("drinks").item(0).getChildNodes();
        for (int i = 0; i < nodeList.getLength(); ++i) {
            Node current = nodeList.item(i);
            if (current.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) current;
                if (element.getNodeName().equals("coffee")) {
                    Coffee coffee = new Coffee();
                    coffee.setName(element.getAttribute("name"));
                    coffee.setCaffeineCount(Integer.parseInt(element.getElementsByTagName("caffeineCount").item(0).getTextContent()));
                    coffee.setPrice(Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()));
                    coffee.setCoffeeType(CoffeeType.valueOf(element.getElementsByTagName("type").item(0).getTextContent()));
                    arrayList.add(coffee);
                } else {
                    Tea tea = new Tea();
                    tea.setName(element.getAttribute("name"));
                    tea.setCaffeineCount(Integer.parseInt(element.getElementsByTagName("caffeineCount").item(0).getTextContent()));
                    tea.setPrice(Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()));
                    tea.setTeaType(TeaType.valueOf(element.getElementsByTagName("type").item(0).getTextContent()));
                    arrayList.add(tea);
                }
            }
        }
    }
}
