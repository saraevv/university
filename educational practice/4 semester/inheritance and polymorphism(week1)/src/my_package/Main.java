package my_package;

public class Main {
    public static void main(String[] args) {
        Directory directory = new Directory("C:\\my_files", "text_files");
        TextFile textFile1 = new TextFile("textFile1", directory);
        TextFile textFile2 = new TextFile("textFile2", directory);
        TextFile textFile3 = new TextFile("textFile3", directory);
        TextFile textFile4 = new TextFile("textFile4", directory);
        textFile1.create("qwe", "asd", "zxc");
        textFile2.create("qaz", "wsx", "edc");
        textFile3.create("123", "456", "789");
        textFile4.create("rty", "fgh", "vbn");
        directory.add(textFile1);
        directory.add(textFile2);
        directory.add(textFile3);
        directory.add(textFile4);
        directory.printAll();
    }
}
