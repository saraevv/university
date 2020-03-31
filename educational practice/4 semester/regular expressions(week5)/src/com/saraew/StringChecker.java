package com.saraew;

import java.util.ArrayList;
import java.util.regex.Pattern;

public class StringChecker {
    private static final Pattern naturalNumberPattern = Pattern.compile("[1-9]\\d*");
    private static final Pattern integerPattern = Pattern.compile("(-?[1-9]\\d*)|0");
    private static final Pattern floatPattern = Pattern.compile("(-?[1-9]\\d*.\\d*[1-9])|(-?0.\\d*[1-9])|(-?\\d.\\d*[1-9]e-?[1-9]\\d*)");
    private static final Pattern datePattern = Pattern.compile(
            "((((0?[1-9])|([1-2]\\d)).(2|02))|(((0?[1-9])|([1-2]\\d)|30).((1|01)|(3|03)|(5|05)|(7|07)|(8|08)|10|12))|" +
                    "(((0?[1-9])|([1-2]\\d)|30|31).((1|01)|(3|03)|(5|05)|(7|07)|(8|08)|10|12))).[1-9]\\d*"
    );
    private static final Pattern timePattern = Pattern.compile("(((0?[1-9])|(1[0-2])):((0?[1-9])|([1-5]\\d)) (am|pm))|" +
            "((0?[1-9])|(1[0-2])|(2[0-4])):((0?[1-9])|([1-5]\\d))");
    private static final Pattern emailPattern = Pattern.compile("[a-zA-z_][a-zA-Z_.]*[a-zA-Z_]@[a-z]+.((com)|(org)|(by)|(ru)|(ua))");


    public static boolean check(String type, String string) {
        switch (type) {
            case "natural number":
                return naturalNumberPattern.matcher(string).matches();
            case "integer":
                return integerPattern.matcher(string).matches();
            case "float":
                return floatPattern.matcher(string).matches();
            case "date":
                return datePattern.matcher(string).matches();
            case "time":
                return timePattern.matcher(string).matches();
            case "email":
                return emailPattern.matcher(string).matches();
            default:
                return false;
        }
    }

    public static ArrayList<String> parse(String data) {
        ArrayList<String> parsedData = new ArrayList<>();
        String[] strings = data.split("[ \n]");
        for (String string : strings) {
            if (datePattern.matcher(string).matches()) {
                parsedData.add(string);
            }
        }
        return parsedData;
    }
}
