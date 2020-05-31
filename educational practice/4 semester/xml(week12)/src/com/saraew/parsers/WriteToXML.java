package com.saraew.parsers;

import com.saraew.data.Student;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.ArrayList;

public class WriteToXML {
    public static void write(File file, ArrayList<Student> students) throws ParserConfigurationException, TransformerException {
        Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
        document.setXmlStandalone(true);
        Element root = document.createElement("students");
        document.appendChild(root);
        for (int i = 0; i < students.size(); ++i) {
            Student student = students.get(i);
            Element element = document.createElement("student");
            element.setAttribute("course", Integer.toString(student.getCourse()));
            element.setAttribute("group", Integer.toString(student.getGroup()));
            Element name = document.createElement("name");
            name.setTextContent(student.getName());
            Element isAdmittedToExams = document.createElement("isAdmittedToExams");
            isAdmittedToExams.setTextContent(Boolean.toString(student.getIsAdmittedToExams()));
            element.appendChild(name);
            element.appendChild(isAdmittedToExams);
            root.appendChild(element);
        }
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.setOutputProperty(OutputKeys.STANDALONE, "yes");
        DOMSource source = new DOMSource(document);
        StreamResult streamResult = new StreamResult(file);
        transformer.transform(source, streamResult);
    }
}
