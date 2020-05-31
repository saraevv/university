package com.saraew.view;

import com.saraew.data.Student;
import com.saraew.parsers.Parsers;
import com.saraew.parsers.WriteToXML;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.*;
import java.util.ArrayList;

public class Main extends Application {
    private ObservableList<Student> students;
    private TableView<Student> tableView;

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("XML");
        primaryStage.getIcons().add(new Image("file:icon.png"));

        MenuBar menuBar = new MenuBar();
        Menu file = new Menu("File");
        Menu option = new Menu("Options");
        Menu openAndCalculate = new Menu("Open and calculate");
        Menu openFile = new Menu("Open");
        Menu saveFile = new Menu("Save");
        MenuItem openXML = new MenuItem("Open xml");
        MenuItem openBin = new MenuItem("Open bin");
        MenuItem saveXML = new MenuItem("Save xml");
        MenuItem saveBin = new MenuItem("Save bin");
        MenuItem calculateCount = new MenuItem("Calculate count of not allowed");
        MenuItem calculateMaximum = new MenuItem("Calculate most frequent group");
        MenuItem delete = new MenuItem("Delete");

        openFile.getItems().add(openXML);
        openFile.getItems().add(openBin);
        saveFile.getItems().add(saveXML);
        saveFile.getItems().add(saveBin);
        file.getItems().add(openFile);
        file.getItems().add(saveFile);
        option.getItems().add(delete);
        file.getItems().add(openAndCalculate);
        openAndCalculate.getItems().add(calculateCount);
        openAndCalculate.getItems().add(calculateMaximum);
        menuBar.getMenus().add(file);
        menuBar.getMenus().add(option);

        VBox vBox = new VBox();

        students = FXCollections.observableArrayList();

        tableView = new TableView<>(students);
        TableColumn<Student, String> names = new TableColumn<>("Name");
        names.setCellValueFactory(new PropertyValueFactory<>("name"));
        TableColumn<Student, Integer> courses = new TableColumn<>("Course");
        courses.setCellValueFactory(new PropertyValueFactory<>("course"));
        TableColumn<Student, Integer> groups = new TableColumn<>("Group");
        groups.setCellValueFactory(new PropertyValueFactory<>("group"));
        TableColumn<Student, Boolean> exams = new TableColumn<>("Is admitted to exams");
        exams.setCellValueFactory(new PropertyValueFactory<>("isAdmittedToExams"));

        names.prefWidthProperty().bind(tableView.widthProperty().multiply(0.25));
        courses.prefWidthProperty().bind(tableView.widthProperty().multiply(0.25));
        groups.prefWidthProperty().bind(tableView.widthProperty().multiply(0.25));
        exams.prefWidthProperty().bind(tableView.widthProperty().multiply(0.24));

        names.setResizable(false);
        courses.setResizable(false);
        groups.setResizable(false);
        exams.setResizable(false);

        tableView.getColumns().addAll(names, courses, groups, exams);

        vBox.getChildren().add(tableView);

        BorderPane borderPane = new BorderPane();
        borderPane.setTop(menuBar);
        borderPane.setCenter(vBox);

        Scene scene = new Scene(borderPane, 600, 400);
        primaryStage.setScene(scene);
        primaryStage.show();

        openXML.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("xml files (*.xml)", "*.xml"));
            File xmlFile = fileChooser.showOpenDialog(primaryStage);
            if (xmlFile != null) {
                try {
                    students = FXCollections.observableArrayList(Parsers.ParseStudent(xmlFile));
                    tableView.setItems(students);
                } catch (ParserConfigurationException | IOException | SAXException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong input");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        openBin.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("bin files (*.bin)", "*.bin"));
            File binFile = fileChooser.showOpenDialog(primaryStage);
            if (binFile != null) {
                try {
                    ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(binFile));
                    students = FXCollections.observableArrayList((ArrayList<Student>) inputStream.readObject());
                    tableView.setItems(students);
                } catch (IOException | ClassNotFoundException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong input");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        saveXML.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("xml files (*.xml)", "*.xml"));
            File xmlFile = fileChooser.showSaveDialog(primaryStage);
            if (xmlFile != null) {
                try {
                    WriteToXML.write(xmlFile, new ArrayList<>(students));
                } catch (ParserConfigurationException | TransformerException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong output");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        saveBin.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("bin files (*.bin)", "*.bin"));
            File binFile = fileChooser.showSaveDialog(primaryStage);
            if (binFile != null) {
                try {
                    ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(binFile));
                    outputStream.writeObject(new ArrayList<>(students));
                } catch (IOException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong output");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        calculateCount.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("xml files (*.xml)", "*.xml"));
            File xmlFile = fileChooser.showOpenDialog(primaryStage);
            if (xmlFile != null) {
                try {
                    int res = Parsers.CalculateCount(xmlFile);
                    Alert result = new Alert(Alert.AlertType.INFORMATION);
                    result.setTitle("Result");
                    result.setHeaderText("Result of calculation");
                    result.setContentText("Result of count of not allowed: " + res);
                    result.showAndWait();
                } catch (ParserConfigurationException | IOException | SAXException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong input");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        calculateMaximum.setOnAction(event -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setInitialDirectory(new File("."));
            fileChooser.getExtensionFilters().add(
                    new FileChooser.ExtensionFilter("xml files (*.xml)", "*.xml"));
            File xmlFile = fileChooser.showOpenDialog(primaryStage);
            if (xmlFile != null) {
                try {
                    int res = Parsers.CalculateMaximum(xmlFile);
                    Alert result = new Alert(Alert.AlertType.INFORMATION);
                    result.setTitle("Result");
                    result.setHeaderText("Result of calculation");
                    result.setContentText("Result of count of most frequent group: " + res);
                    result.showAndWait();
                } catch (ParserConfigurationException | IOException | SAXException e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error");
                    alert.setHeaderText("Wrong input");
                    alert.setContentText("Something went wrong. Try again.");
                    alert.showAndWait();
                }
            }
        });

        delete.setOnAction(event -> {
            delete();
        });
    }

    private void delete() {
        if (!students.isEmpty()) {
            Student student = tableView.getSelectionModel().getSelectedItem();
            students.remove(student);
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
