package com.saraew;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.Tab;
import javafx.scene.control.TextArea;
import javafx.scene.layout.VBox;


public class SecondTask extends Tab {
    private TextArea textArea;
    ObservableList<String> data;

    public SecondTask() {
        this.setText("Second Task");

        VBox layout = new VBox();
        layout.setAlignment(Pos.CENTER);

        textArea = new TextArea();
        textArea.setMinHeight(200);

        data = FXCollections.observableArrayList();
        ListView<String> list = new ListView<>(data);

//        Button button = new Button("Parse");
//        button.setOnAction(event -> {
//            data.clear();
//            data.addAll(StringChecker.parse(textArea.getText()));
//        });

        textArea.textProperty().addListener((ov, oldV, newV) -> {
            if (!newV.trim().isEmpty()) {
                data.clear();
                data.addAll(StringChecker.parse(textArea.getText()));
            }
        });

        layout.getChildren().addAll(textArea, list);
        this.setContent(layout);
    }
}
