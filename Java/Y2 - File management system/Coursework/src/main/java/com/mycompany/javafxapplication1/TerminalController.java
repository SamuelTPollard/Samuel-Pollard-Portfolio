package com.mycompany.javafxapplication1;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMain.java to edit this template
 */
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

/**
 *
 * @author ntu-user
 */
public class TerminalController  {

    @FXML
    private Button Exitbtn;

    @FXML
    private TextArea ConsoleTxt;

    @FXML
    private TextField InpTxt;

  
    @FXML
    private void switchToPrimary() {
        Stage primaryStage = new Stage();
        Stage terminalStage = (Stage) Exitbtn.getScene().getWindow();
        try {

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("primary.fxml"));
            Parent root = loader.load();
            Scene scene = new Scene(root, 640, 480);
            primaryStage.setScene(scene);
            primaryStage.setTitle("Login");
            primaryStage.show();
            terminalStage.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void submitCommand() {
        String Command = InpTxt.getText();
        InpTxt.setText("");
        ConsoleTxt.appendText(Command + '\n');
        ConsoleTxt.appendText(Terminal.RunCommand(Command) + '\n');
    }

    /**
     * @param args the command line arguments
     */
}
