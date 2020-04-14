package com.saraew;

import javafx.embed.swing.SwingFXUtils;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.util.Pair;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

public class Controller {
    private ArrayList<Pair<BufferedImage, Integer>> images;
    private Stage primaryStage;
    private static final int TABLE_WEIGHT = 640, TABLE_HEIGHT = 360,
            CELL_WEIGHT = 160, CELL_HEIGHT = 90, ROW_COUNT = 4, COLUMN_COUNT = 4;
    private Pair<Integer, Integer> firstPair, secondPair;
    private boolean firstClick = true, position = true;

    @FXML
    private GridPane pane;
    @FXML
    private Label status;
    @FXML
    private ImageView correctImage;
    @FXML
    private TextField inputField;
    @FXML
    private Button changePosition;
    @FXML
    private Canvas canvas;


    EventHandler<MouseEvent> vBoxHandle;

    public Controller(Stage primaryStage) {
        this.primaryStage = primaryStage;
        images = new ArrayList<>();
        vBoxHandle = new EventHandler<>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                Node source = (Node) mouseEvent.getSource();
                Pair<Integer, Integer> coord = new Pair<>(GridPane.getRowIndex(source), GridPane.getColumnIndex(source));
                if (firstClick) {
                    firstPair = coord;
                } else {
                    secondPair = coord;
                    swapCellsData();
                }
                firstClick = !firstClick;
            }
        };
    }

    public void initialize() {
        pane.getStyleClass().add("image-grid");
        inputField.textProperty().addListener((ov, oldV, newV) -> {
            editText();
        });
    }

    @FXML
    public void openImage(ActionEvent event) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setInitialDirectory(new File("."));
        File selectedFile = fileChooser.showOpenDialog(primaryStage);
        if (selectedFile != null) {
            try {
                setImages(ImageIO.read(selectedFile));
            } catch (IOException e) {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Ошибка");
                alert.setHeaderText("Неправильный ввод");
                alert.setContentText("Выбран некорректный файл");
                alert.showAndWait();
            }
        }
    }

    public void setImages(BufferedImage image) {
        images.clear();
        BufferedImage redImage = new BufferedImage(TABLE_WEIGHT, TABLE_HEIGHT, BufferedImage.TYPE_INT_RGB);
        java.awt.Graphics g = redImage.getGraphics();
        g.drawImage(image, 0, 0, TABLE_WEIGHT, TABLE_HEIGHT, null);
        correctImage.setImage(SwingFXUtils.toFXImage(redImage, null));
        int pos = 0;
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < COLUMN_COUNT; ++j, ++pos) {
                images.add(new Pair<BufferedImage, Integer>(redImage.getSubimage(j * CELL_WEIGHT, i * CELL_HEIGHT, CELL_WEIGHT, CELL_HEIGHT), pos));
            }
        }
        Collections.shuffle(images);
        repaint();
        checkOrder();
    }

    private void repaint() {
        int pos = 0;
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < COLUMN_COUNT; ++j, ++pos) {
                VBox vBox = new VBox();
                vBox.getStyleClass().add("image-grid-cell");
                vBox.getChildren().add(new ImageView(SwingFXUtils.toFXImage(images.get(pos).getKey(), null)));
                vBox.setOnMouseClicked(vBoxHandle);
                pane.add(vBox, j, i);
            }
        }
    }

    private void swapCellsData() {
        int firstIndex = firstPair.getKey() * ROW_COUNT + firstPair.getValue(), secondIndex = secondPair.getKey() * ROW_COUNT + secondPair.getValue();
        Pair<BufferedImage, Integer> firstElem = images.get(firstIndex);
        Pair<BufferedImage, Integer> secondElem = images.get(secondIndex);
        images.set(firstIndex, secondElem);
        images.set(secondIndex, firstElem);

        firstPair = new Pair<>(-1, -1);
        secondPair = new Pair<>(-1, -1);
        checkOrder();
        repaint();
    }

    private void checkOrder() {
        int pos = 0;
        boolean flag = true;
        for (int i = 0; i < 16; ++i, ++pos) {
            if (images.get(pos).getValue() != pos) {
                flag = false;
                break;
            }
        }
        if (flag) {
            status.setText("Correct image");
            status.setTextFill(Color.GREEN);
        } else {
            status.setText("Incorrect image");
            status.setTextFill(Color.RED);
        }
    }

    private void editText() {
        String str = inputField.getText();
        GraphicsContext graphicsContext = canvas.getGraphicsContext2D();
        graphicsContext.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        double x0 = 25, y0 = canvas.getHeight() / 2;
        Font font = Font.font("Verdana", FontWeight.BOLD, 75);
        graphicsContext.setFont(font);
        if (position) {
            graphicsContext.setFill(Color.RED);
            for (int i = 0; i < 8; ++i, --x0, --y0) {
                graphicsContext.fillText(str, x0, y0);
            }
        } else {
            graphicsContext.setFill(Color.BLUE);
            for (int i = 0; i < 8; ++i, ++x0, --y0) {
                graphicsContext.fillText(str, x0, y0);
            }
        }

    }

    @FXML
    public void changePosition() {
        position = !position;
        editText();
    }

}
