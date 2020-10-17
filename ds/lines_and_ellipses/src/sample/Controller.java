package sample;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Cursor;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.MenuBar;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.util.Pair;


public class Controller {
    boolean firstClick = true;
    double firstCoordinateX, firstCoordinateY;
    Mode mode = Mode.LINE;

    @FXML
    private Canvas canvas;

    @FXML
    public void exit(ActionEvent event) {
        Platform.exit();
        System.exit(0);
    }

    @FXML
    public void setMode(ActionEvent event) {
        Button button = (Button) event.getSource();
        switch (button.getText()) {
            case "Line":
                mode = Mode.LINE;
                break;
            case "Ellipse":
                mode = Mode.ELLIPSE;
                break;
        }
    }

    public void initialize() {
        canvas.setCursor(Cursor.CROSSHAIR);
        canvas.setOnMouseClicked(event -> {
            if (firstClick) {
                firstClick = false;
                firstCoordinateX = event.getX();
                firstCoordinateY = event.getY();
            } else {
                firstClick = true;
                GraphicsContext graphicsContext = canvas.getGraphicsContext2D();
                switch (mode) {
                    case LINE:
                        graphicsContext.strokeLine(firstCoordinateX, firstCoordinateY, event.getX(), event.getY());
                        break;
                    case ELLIPSE:
                        graphicsContext.strokeOval(firstCoordinateX, firstCoordinateY, event.getX(), event.getY());
                }
            }
        });
    }
}
