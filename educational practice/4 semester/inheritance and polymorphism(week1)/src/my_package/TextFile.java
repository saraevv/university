package my_package;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class TextFile extends File {
    private ArrayList<String> data;

    public TextFile() {
        super();
    }

    public TextFile(String name, Directory directory) {
        super(name, directory);
    }

    public void create(String... strings) {
        data = new ArrayList<String>();
        data.addAll(Arrays.asList(strings));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        TextFile textFile = (TextFile) o;
        return Objects.equals(data, textFile.data);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), data);
    }

    @Override
    public String toString() {
        StringBuffer buffer = new StringBuffer("Text file:\n\t" + super.toString() + '\n');
        for (String s : data) {
            buffer.append("\t\t" + s + '\n');
        }
        return new String(buffer);
    }

    public void add(String string) {
        data.add(string);
    }

    public void delete() {
        data.clear();
    }
}
