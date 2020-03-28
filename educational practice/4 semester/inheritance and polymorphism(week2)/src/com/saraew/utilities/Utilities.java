package com.saraew.utilities;

import com.saraew.plans.*;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.awt.image.AreaAveragingScaleFilter;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Utilities {
    public static void viewPlanList(ArrayList<Plan> plans) {
        for (Plan plan : plans) {
            System.out.println(plan);
        }
    }

    public static void sortPlans(ArrayList<Plan> plans) {
        Collections.sort(plans, new Comparator<Plan>() {
            @Override
            public int compare(Plan plan, Plan t1) {
                return plan.getUsers() - t1.getUsers();
            }
        });
    }

    public static void totalCountOfUsers(ArrayList<Plan> plans) {
        int ans = 0;
        for (Plan plan : plans) {
            ans += plan.getUsers();
        }
        System.out.println(ans);
    }

    public static ArrayList<Plan> findPlan(ArrayList<Plan> plans, Plan plan) {
        ArrayList<Plan> ans = new ArrayList<>();
        for(Plan p:plans) {
            if(p.isCorrespond(plan)) {
                ans.add(p);
            }
        }
        return ans;
    }

    public static void parseFromXml(ArrayList<Plan> plans) throws ParserConfigurationException, IOException, SAXException {
        plans.clear();
        DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = builder.parse(new File("E:\\university\\educational practice\\4 semester\\inheritance and polymorphism(week2)\\src\\input.xml"));
        document.getDocumentElement().normalize();
        NodeList list = document.getElementsByTagName("plan");
        for (int i = 0; i < list.getLength(); ++i) {
            Node node = list.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;
                switch (list.item(i).getAttributes().getNamedItem("type").getNodeValue()) {
                    case "UnlimitedMobile":
                        plans.add(new UnlimitedMobilePlan(element.getElementsByTagName("name").item(0).getTextContent(),
                                Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("users").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("isshared").item(0).getTextContent())));
                        break;
                    case "MobileCalls":
                        plans.add(new MobilePlanForCalls(element.getElementsByTagName("name").item(0).getTextContent(),
                                Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("users").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("callsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("smsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("internetprice").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("callscount").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("favcount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("iscallsunlimited").item(0).getTextContent())));
                        break;
                    case "MobileCallsSMS":
                        plans.add(new MobilePlanForCallsAndSMS(element.getElementsByTagName("name").item(0).getTextContent(),
                                Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("users").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("callsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("smsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("internetprice").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("callscount").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("favcount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("iscallsunlimited").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("smscount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("issmsunlimited").item(0).getTextContent())));
                        break;
                    case "MobileEverything":
                        plans.add(new MobilePlanForEverything(element.getElementsByTagName("name").item(0).getTextContent(),
                                Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("users").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("callsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("smsprice").item(0).getTextContent()),
                                Double.parseDouble(element.getElementsByTagName("internetprice").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("callscount").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("favcount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("iscallsunlimited").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("smscount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("issmsunlimited").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("internetcount").item(0).getTextContent()),
                                Boolean.parseBoolean(element.getElementsByTagName("issmsunlimited").item(0).getTextContent())));
                        break;
                    case "Computer":
                        plans.add(new ComputerPlan(element.getElementsByTagName("name").item(0).getTextContent(),
                                Integer.parseInt(element.getElementsByTagName("price").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("users").item(0).getTextContent()),
                                Integer.parseInt(element.getElementsByTagName("internetspeed").item(0).getTextContent())));
                        break;
                }
            }
        }
    }
}
