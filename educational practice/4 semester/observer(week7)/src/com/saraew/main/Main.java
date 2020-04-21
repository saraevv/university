package com.saraew.main;

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class Main extends Application {
    private ObservableList observableList;

    @Override
    public void start(Stage stage) throws Exception {
        ObserverList list = new ObserverList();
        ObserverLabel label = new ObserverLabel();
        observableList = new ObservableList();
        observableList.addObserver(label);
        observableList.addObserver(list);

        HBox hBox = new HBox();
        label.setPrefSize(300, 400);
        label.setAlignment(Pos.CENTER);
        label.setFont(Font.font(30));
        list.setPrefSize(300, 400);
        hBox.getChildren().addAll(label, list);
        Scene scene = new Scene(hBox, 600, 400);
        stage.setTitle("Observer");
        stage.setScene(scene);
        stage.show();

        scene.setOnKeyTyped(keyEvent -> {
            observableList.setCurrent(keyEvent.getCharacter());
        });
    }

    public static void main(String[] args) {
        launch(args);
    }
}
