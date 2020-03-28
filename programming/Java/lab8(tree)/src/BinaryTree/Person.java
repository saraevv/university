package BinaryTree;

import java.util.StringTokenizer;

public class Person implements Comparable<Person> {

    private String first;
    private String second;

    public Person(String p) {
        StringTokenizer st = new StringTokenizer(p);
        first = st.nextToken();
        second = st.nextToken();
    }

    @Override
    public int compareTo(Person person) {
//        if(first.compareTo(person.first)!=0)
//            return first.compareTo(person.first);
//        else
//            return second.compareTo(person.second);
        return first.compareTo(person.first) == 0 ?
                first.compareTo(person.first) : second.compareTo(person.second);
    }

    @Override
    public String toString() {
        return new String('\u0022' + first + " " + second + '\u0022');
    }

}
