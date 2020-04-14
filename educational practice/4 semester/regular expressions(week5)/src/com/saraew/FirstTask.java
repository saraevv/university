package com.saraew;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Pos;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Tab;
import javafx.scene.control.TextField;
import javafx.scene.layout.FlowPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class FirstTask extends Tab {
    private ChoiceBox<String> choiceBox;
    private TextField textField;
    private Circle circle;

    public FirstTask() {
        this.setText("First Task");

        FlowPane pane = new FlowPane(10, 10);
        pane.setAlignment(Pos.CENTER);

        ObservableList<String> data = FXCollections.observableArrayList("natural number",
                "integer", "float", "date", "time", "email");
        choiceBox = new ChoiceBox<>(data);
        choiceBox.setValue("natural number");
        choiceBox.setOnAction(event -> FirstTask.this.checkText());

        textField = new TextField();

        textField.textProperty().addListener((ov, oldV, newV) -> {
            if (!newV.trim().isEmpty()) {
                FirstTask.this.checkText();
            }
        });

        circle = new Circle();
        circle.setRadius(7);
        circle.setFill(Color.RED);

        pane.getChildren().addAll(choiceBox, textField, circle);
        this.setContent(pane);
    }

    private void checkText() {
        if (StringChecker.check(choiceBox.getValue(), textField.getText())) {
            circle.setFill(Color.GREEN);
        } else {
            circle.setFill(Color.RED);
        }
    }
}
