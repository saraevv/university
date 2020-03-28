package my_package;

import java.util.Objects;

public class File {
    private String name;
    private Directory directory;

    public File() {
    }

    public File(String name, Directory directory) {
        this.name = name;
        this.directory = directory;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Directory getDirectory() {
        return directory;
    }

    public void setDirectory(Directory directory) {
        this.directory = directory;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        File file = (File) o;
        return Objects.equals(name, file.name) &&
                Objects.equals(directory, file.directory);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, directory);
    }

    @Override
    public String toString() {
        return "name:\"" + name + "\", directory:\"" + directory.getPath() + '\\' + directory.getName() + '\"';
    }


    public void printOnConsole() {
        System.out.println(this);
    }
}
