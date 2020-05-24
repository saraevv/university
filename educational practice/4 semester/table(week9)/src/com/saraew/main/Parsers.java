package com.saraew.main;

import com.saraew.stuff.Pair;
import com.saraew.returns.*;

import java.util.GregorianCalendar;
import java.util.regex.Pattern;

public class Parsers {

    private static final Pattern datePattern = Pattern.compile(
            "((((0?[1-9])|([1-2]\\d))\\.(2|02))|(((0?[1-9])|([1-2]\\d)|30)\\.((4|04)|(6|06)|(5|05)|(9|09)|11))|" +
                    "(((0?[1-9])|([1-2]\\d)|30|31)\\.((1|01)|(3|03)|(5|05)|(7|07)|(8|08)|10|12)))\\.[1-9]\\d*"
    );

    private static final Pattern linkPattern = Pattern.compile("\\D\\d");

    private static final Pattern dateConstantPattern = Pattern.compile(
            "(((((0?[1-9])|([1-2]\\d))\\.(2|02))|(((0?[1-9])|([1-2]\\d)|30)\\.((4|04)|(6|06)|(5|05)|(9|09)|11))|" +
                    "(((0?[1-9])|([1-2]\\d)|30|31)\\.((1|01)|(3|03)|(5|05)|(7|07)|(8|08)|10|12)))\\.[1-9]\\d*)(\\+|\\-)" +
                    "(([1-9]\\d*)|0)"
    );

    private static final Pattern linkConstantPattern = Pattern.compile(
            "(\\D\\d)(\\+|\\-)(([1-9]\\d*)|0)"
    );

    private static final Pattern minPattern = Pattern.compile(
            "min\\(" + "((" + linkPattern.pattern() + ")" + "|" + "(" + datePattern.pattern() + "))" +
                    "(\\," + "((" + linkPattern.pattern() + ")" + "|" + "(" + datePattern.pattern() + "))" + ")*" +
                    "\\)"
    );

    private static final Pattern maxPattern = Pattern.compile(
            "max\\(" + "((" + linkPattern.pattern() + ")" + "|" + "(" + datePattern.pattern() + "))" +
                    "(\\," + "((" + linkPattern.pattern() + ")" + "|" + "(" + datePattern.pattern() + "))" + ")*" +
                    "\\)"
    );

    public static boolean check(String s) {
        return s.length() == 0 ||
                datePattern.matcher(s).matches() ||
                linkPattern.matcher(s).matches() ||
                dateConstantPattern.matcher(s).matches() ||
                linkConstantPattern.matcher(s).matches() ||
                minPattern.matcher(s).matches() ||
                maxPattern.matcher(s).matches();
    }

    public static Return getValue(String s) {
        Return r;
        if(s.length() == 0) {
            return new EmptyReturn();
        }
        else if (datePattern.matcher(s).matches()) {
            r = new DateConstantReturn(getDate(s), 0);
        } else if (linkPattern.matcher(s).matches()) {
            Pair<Integer, Integer> p = getLink(s);
            r = new LinkConstantReturn(p.getFirst(), p.getSecond(), 0);
        } else if (dateConstantPattern.matcher(s).matches() ||
                linkConstantPattern.matcher(s).matches()) {
            boolean flag = false;
            String[] strings;
            if (s.contains("+")) {
                strings = s.split("\\+");
                flag = true;
            } else {
                strings = s.split("\\-");
            }
            int constant = Integer.parseInt(strings[1]);
            if (!flag) {
                constant *= -1;
            }
            if (dateConstantPattern.matcher(s).matches()) {
                r = new DateConstantReturn(getDate(strings[0]), constant);
            } else {
                Pair<Integer, Integer> p = getLink(strings[0]);
                r = new LinkConstantReturn(p.getFirst(), p.getSecond(), constant);
            }
        } else {
            r = new MinMaxReturn(minPattern.matcher(s).matches());
            String[] strings = s.substring(4, s.length() - 1).split(",");
            for (String str : strings) {
                if (datePattern.matcher(str).matches()) {
                    ((MinMaxReturn) r).append(new DateConstantReturn(getDate(str), 0));
                } else {
                    Pair<Integer, Integer> p = getLink(str);
                    ((MinMaxReturn) r).append(new LinkConstantReturn(p.getFirst(), p.getSecond(), 0));
                }
            }
        }
        return r;
    }


    private static GregorianCalendar getDate(String s) {
        String[] strings = s.split("\\.");
        return new GregorianCalendar(Integer.parseInt(strings[2]),
                Integer.parseInt(strings[1]) - 1, Integer.parseInt(strings[0]));
    }

    private static Pair<Integer, Integer> getLink(String s) {
        char c = s.charAt(0);
        String[] strings = s.split(Character.toString(c));
        int i1 = Integer.parseInt(strings[1]);
        int i2 = (char) (c - 'A') + 1;
        return new Pair<>(i1, i2);
    }

}
