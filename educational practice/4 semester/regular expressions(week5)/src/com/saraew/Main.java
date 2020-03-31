package com.saraew;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.TabPane;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("regular expressions");
        primaryStage.getIcons().add(new Image("file:./icon.png"));

        FirstTask firstTask = new FirstTask();
        SecondTask secondTask = new SecondTask();

        TabPane tabPane = new TabPane();
        tabPane.getTabs().add(firstTask);
        tabPane.getTabs().add(secondTask);

        primaryStage.setScene(new Scene(tabPane, 600, 400));
        primaryStage.show();
    }
}