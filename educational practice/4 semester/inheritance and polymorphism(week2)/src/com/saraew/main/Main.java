package com.saraew.main;

import com.saraew.plans.Plan;
import com.saraew.utilities.Menu;
import com.saraew.utilities.Utilities;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ArrayList<Plan> plans = new ArrayList<>();
        try {
            Utilities.parseFromXml(plans);
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        }

        Menu menu = new Menu(new Scanner(System.in), plans);
        menu.run();
    }
}
