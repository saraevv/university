package com.saraew;

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
import java.util.Map;

public class CountryParser {
    public static void parseFromXML(String path, Map<String, Country> countryMap) throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(new File(path));
        document.getDocumentElement().normalize();
        NodeList list = document.getElementsByTagName("country");
        for (int i = 0; i < list.getLength(); ++i) {
            Node node = list.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;
                String name = element.getElementsByTagName("name").item(0).getTextContent();
                Country country = new Country(name, element.getElementsByTagName("capital").item(0).getTextContent(),
                        element.getElementsByTagName("path").item(0).getTextContent(),
                        element.getElementsByTagName("description").item(0).getTextContent(),
                        Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()));
                countryMap.put(name, country);
            }
        }

    }
}
