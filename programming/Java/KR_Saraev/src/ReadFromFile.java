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

public class ReadFromFile {
    public static ArrayList<AbstractWorker> readXml(File file) throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(file);
        NodeList nodeList = document.getElementsByTagName("workers").item(0).getChildNodes();
        ArrayList<AbstractWorker> arrayList = new ArrayList<>();
        for (int i = 0; i < nodeList.getLength(); ++i) {
            Node current = nodeList.item(i);
            if (current.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) current;
                if (element.getNodeName().equals("security")) {
                    Security security = new Security();
                    security.setName(element.getAttribute("name"));
                    security.setOrganization(element.getAttribute("organization"));
                    security.setArea(Double.parseDouble(element.getElementsByTagName("area").item(0).getTextContent()));
                    security.setCoefficient(Double.parseDouble(element.getElementsByTagName("coefficient").item(0).getTextContent()));
                    arrayList.add(security);
                } else {
                    Seller seller = new Seller();
                    seller.setName(element.getAttribute("name"));
                    seller.setOrganization(element.getAttribute("organization"));
                    seller.setProceeds(Double.parseDouble(element.getElementsByTagName("proceeds").item(0).getTextContent()));
                    seller.setCoefficient(Double.parseDouble(element.getElementsByTagName("coefficient").item(0).getTextContent()));
                    arrayList.add(seller);
                }
            }
        }
        return arrayList;
    }
}
