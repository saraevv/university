package com.saraew.utilities;

import com.saraew.plans.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Menu implements Runnable {
    Scanner scanner;
    ArrayList<Plan> plans;


    public Menu(Scanner scanner, ArrayList<Plan> plans) {
        this.scanner = scanner;
        this.plans = plans;
    }

    @Override
    public void run() {
        do {
            System.out.println("Choose option:\n\t1.View plans list\n\t2.Find plan\n\t3.Sort plans\n\t4.Total count of users\n\t0.Exit");
            switch (getAnswer()) {
                case 1:
                    Utilities.viewPlanList(plans);
                    break;
                case 2:
                    findPlan();
                    break;
                case 3:
                    Utilities.sortPlans(plans);
                    break;
                case 4:
                    Utilities.totalCountOfUsers(plans);
                    break;
                case 0:
                    return;
                default:
                    System.out.println("Wrong input");
            }
        } while (wouldYouLikeToContinue());
    }

    private boolean wouldYouLikeToContinue() {
        System.out.println("Would you like to continue?\n\t1.Yes\n\t0.No");
        return getAnswer() != 0;
    }

    private void findPlan() {
        ArrayList<Plan> ans = new ArrayList<>();
        System.out.println("Choose plan type:\n\t1.Mobile plan\n\t2.Computer plan");
        int option = 0;
        do {
            option = getAnswer();
        } while (option != 1 && option != 2);

        if (option == 1) {
            System.out.println("Choose plan type:\n\t1.For calls\n\t2.For calls and SMS\n\t3.For calls, SMS, ans internet\n\t4.Unlimited plan");
            do {
                option = getAnswer();
            } while (option != 1 && option != 2 && option != 3 && option != 4);
            System.out.println("Write following parameters:");
            switch (option) {
                case 1:
                    System.out.print("Price, price of calls, price of SMS, price of internet");
                    System.out.println(", count of minutes, count of free numbers, is calls unlimited");
                    ans = Utilities.findPlan(plans, new MobilePlanForCalls("", 0, scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(), scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(), scanner.nextBoolean()));
                    break;
                case 2:
                    System.out.print("Price, price of calls, price of SMS, price of internet");
                    System.out.println(", count of minutes, count of free numbers, is calls unlimited,\n" +
                            "count of SMS, is SMS unlimited");
                    ans = Utilities.findPlan(plans, new MobilePlanForCallsAndSMS("", 0, scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(), scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(), scanner.nextBoolean(), scanner.nextInt(), scanner.nextBoolean()));
                    break;
                case 3:
                    System.out.print("Price, price of calls, price of SMS, price of internet");
                    System.out.println(", count of minutes, count of free numbers, is calls unlimited,\n" +
                            "count of SMS, is SMS unlimited, count of megabytes, is internet unlimited");
                    ans = Utilities.findPlan(plans, new MobilePlanForEverything("", 0, scanner.nextInt(), scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(),
                            scanner.nextInt(), scanner.nextInt(), scanner.nextBoolean(), scanner.nextInt(), scanner.nextBoolean(),
                            scanner.nextInt(), scanner.nextBoolean()));
                    break;
                case 4:
                    System.out.println("Price, is sharing allowed");
                    ans = Utilities.findPlan(plans, new UnlimitedMobilePlan("", 0, scanner.nextInt(), scanner.nextBoolean()));
                    break;
            }
        } else {
            System.out.println("Write following parameters:\nPrice, internet speed");
            ans = Utilities.findPlan(plans, new ComputerPlan("", 0, scanner.nextInt(), scanner.nextInt()));
        }
        Utilities.viewPlanList(ans);
    }

    private int getAnswer() {
        while (true) {
            try {
                return Integer.parseInt(scanner.next());
            } catch (NumberFormatException e) {
                System.out.println("Wrong input");
            }
        }

    }
}
