package com.saraew;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.net.URL;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader();
        URL fxmlURL = getClass().getResource("window.fxml");
        loader.setLocation(fxmlURL);
        loader.setController(new Controller(primaryStage));
        Parent root = loader.load();
        root.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());
        primaryStage.setTitle("Graphics");
        primaryStage.getIcons().add(new Image("file:./icon.png"));
        primaryStage.setScene(new Scene(root, 1000, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
