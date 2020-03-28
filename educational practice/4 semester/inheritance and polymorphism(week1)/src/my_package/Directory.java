package my_package;

import java.util.ArrayList;
import java.util.Objects;

public class Directory extends ArrayList<File> {
    private String path;
    private String name;

    public Directory(String path, String name) {
        this.path = path;
        this.name = name;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Directory files = (Directory) o;
        return Objects.equals(path, files.path) &&
                Objects.equals(name, files.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), path, name);
    }

    @Override
    public String toString() {
        StringBuffer buffer = new StringBuffer("Directory:\"" + path + '\\' + name + '\"');
        for (File file : this) {
            buffer.append(this);
        }
        return new String(buffer);
    }

    public void printAll() {
        System.out.println("Directory:\"" + path + '\\' + name + '\"');
        for (File file : this) {
            file.printOnConsole();
        }
    }
}
