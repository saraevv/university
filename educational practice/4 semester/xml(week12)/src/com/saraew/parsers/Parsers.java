package com.saraew.parsers;

import com.saraew.data.Student;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;

public class Parsers {
    public static ArrayList<Student> ParseStudent(File file) throws ParserConfigurationException, IOException, SAXException {
        ArrayList<Student> list = new ArrayList<>();
        DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = builder.parse(file);
        document.getDocumentElement().normalize();
        NodeList nodeList = document.getElementsByTagName("student");
        for (int i = 0; i < nodeList.getLength(); ++i) {
            Node node = nodeList.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;
                int group = Integer.parseInt(element.getAttribute("group")),
                        course = Integer.parseInt(element.getAttribute("course"));
                String name = element.getElementsByTagName("name").item(0).getTextContent();
                boolean tr = Boolean.parseBoolean(element.getElementsByTagName("isAdmittedToExams").
                        item(0).getTextContent());
                list.add(new Student(name, course, group, tr));
            }
        }
        return list;
    }

    public static int CalculateCount(File file) throws ParserConfigurationException, SAXException, IOException {
        SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
        MySAXParser saxParserCount = new MySAXParser();
        parser.parse(file, saxParserCount);
        return saxParserCount.getRes();
    }

    public static int CalculateMaximum(File file) throws ParserConfigurationException, SAXException, IOException {
        SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
        MySAXParser saxParserCount = new MySAXParser();
        parser.parse(file, saxParserCount);
        return saxParserCount.getMax();

    }

    private static class MySAXParser extends DefaultHandler {
        private String elem = "";
        private int res = 0;
        private Map<Integer, Integer> groups = new TreeMap<>();

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            elem = qName;
            if (elem.equals("student")) {
                for (int i = 0; i < attributes.getLength(); ++i) {
                    if (attributes.getQName(i).equals("group")) {
                        int val = Integer.parseInt(attributes.getValue(i));
                        if (groups.containsKey(val)) {
                            groups.put(val, groups.get(val) + 1);
                        } else {
                            groups.put(val, 1);
                        }
                    }
                }
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            elem = "";
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            if (elem.equals("isAdmittedToExams")) {
                int val = Integer.parseInt(new String(ch, start, length));
                if (val == 0) {
                    ++res;
                }
            }
        }

        public int getRes() {
            return res;
        }

        public int getMax() {
            int maxKey = 0, maxValue = 0;
            for (Map.Entry<Integer, Integer> entry : groups.entrySet()) {
                if (entry.getValue() > maxValue) {
                    maxValue = entry.getValue();
                    maxKey = entry.getKey();
                }
            }
            return maxKey;
        }
    }
}
