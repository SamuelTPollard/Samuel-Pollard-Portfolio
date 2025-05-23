package com.mycompany.javafxapplication1;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class SecondaryController {

    @FXML
    private TextField userTextField;

    @FXML
    private TableView dataTableView;

    @FXML
    private Button secondaryButton;

    @FXML
    private Button refreshBtn;

    @FXML
    private Button fileBtn;

    @FXML
    private Button encryptBtn;

    @FXML
    private TextField customTextField;

    @FXML
    private void RefreshBtnHandler(ActionEvent event) {
        Stage primaryStage = (Stage) customTextField.getScene().getWindow();
        customTextField.setText((String) primaryStage.getUserData());
    }

    @FXML
    private void fileBtnHandler(ActionEvent event) {
        Stage secondaryStage = new Stage();
        Stage primaryStage = (Stage) customTextField.getScene().getWindow();
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("file.fxml"));
            Parent root = loader.load();
            Scene scene = new Scene(root, 640, 480);
            secondaryStage.setScene(scene);
            secondaryStage.setTitle("File Management");
            secondaryStage.setUserData(userTextField.getText());
            secondaryStage.show();
            FileController controller = loader.getController();
            primaryStage.close();
        } catch (IOException ex) {
            Logger.getLogger(PrimaryController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @FXML
    private void userBtnHandler(ActionEvent event) {
        Stage secondaryStage = new Stage();
        Stage primaryStage = (Stage) customTextField.getScene().getWindow();
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("user.fxml"));
            Parent root = loader.load();
            Scene scene = new Scene(root, 640, 480);
            secondaryStage.setScene(scene);
            secondaryStage.setTitle("User Management");
            secondaryStage.show();
            primaryStage.close();
        } catch (IOException ex) {
            Logger.getLogger(PrimaryController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @FXML
    private void switchToPrimary() {
        Stage secondaryStage = new Stage();
        Stage primaryStage = (Stage) secondaryButton.getScene().getWindow();
        try {

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("primary.fxml"));
            Parent root = loader.load();
            Scene scene = new Scene(root, 640, 480);
            secondaryStage.setScene(scene);
            secondaryStage.setTitle("Login");
            secondaryStage.show();
            primaryStage.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public void initialise(String[] credentials) {
        userTextField.setText(credentials[0]);
        DB myObj = new DB();
        ObservableList<User> data;
        try {
            data = myObj.getDataFromTable();
            TableColumn user = new TableColumn("User");
            user.setCellValueFactory(
                    new PropertyValueFactory<>("user"));

            TableColumn pass = new TableColumn("Pass");
            pass.setCellValueFactory(
                    new PropertyValueFactory<>("pass"));
            dataTableView.setItems(data);
            dataTableView.getColumns().addAll(user, pass);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(SecondaryController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
