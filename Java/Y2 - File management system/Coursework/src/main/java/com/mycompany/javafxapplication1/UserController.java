/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.javafxapplication1;

import java.security.spec.InvalidKeySpecException;
import java.util.Optional;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 *
 * @author ntu-user
 */
public class UserController {

    @FXML
    private Button deleteBtn;

    @FXML
    private Button backLoginBtn;

    @FXML
    private PasswordField existPasswordField;

    @FXML
    private PasswordField newPasswordField;

    @FXML
    private TextField usernameTextField;

    @FXML
    private Text fileText;

    @FXML
    private Button updateBtn;

    DB myObj = new DB();

    @FXML
    private void deleteBtnHandler() throws InvalidKeySpecException, ClassNotFoundException {
        myObj.removeUserFromDB(usernameTextField.getText());
    }

    @FXML
    private void UpdateBtnHandler() throws InvalidKeySpecException, ClassNotFoundException {
        myObj.updateUserPassword(usernameTextField.getText(), existPasswordField.getText(), newPasswordField.getText());
        usernameTextField.setText("");
        existPasswordField.setText("");
        newPasswordField.setText("");
    }

    @FXML
    private void backLoginBtnHandler(ActionEvent event) {
        Stage secondaryStage = new Stage();
        Stage primaryStage = (Stage) backLoginBtn.getScene().getWindow();
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

    private void dialogue(String headerMsg, String contentMsg) {
        Stage secondaryStage = new Stage();
        Group root = new Group();
        Scene scene = new Scene(root, 300, 300, Color.DARKGRAY);
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Confirmation Dialog");
        alert.setHeaderText(headerMsg);
        alert.setContentText(contentMsg);
        Optional<ButtonType> result = alert.showAndWait();
    }
}
