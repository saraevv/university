package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.net.URL;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader loader = new FXMLLoader();
        URL fxmlURL = getClass().getResource("window.fxml");
        loader.setLocation(fxmlURL);
        loader.setController(new Controller());
        Parent root = loader.load();
        primaryStage.setTitle("Lines and ellipses");
        //primaryStage.getIcons().add(new Image("file:./icon.png"));
        //primaryStage.setScene(new Scene(root, 900, 600));

        Scene scene = new Scene(root,900,600);
        scene.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());
        primaryStage.setScene(scene);

        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
