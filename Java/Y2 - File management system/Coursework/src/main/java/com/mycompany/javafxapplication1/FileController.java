/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMain.java to edit this template
 */
package com.mycompany.javafxapplication1;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Optional;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.event.EventHandler;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.ObservableList;
import javafx.scene.Group;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.paint.Color;

/**
 *
 * @author ntu-user
 */
public class FileController {

    @FXML
    private Button returnBtn;

    @FXML
    private TextArea fileNameBox;

    @FXML
    private TextArea fileContentsBox;

    @FXML
    private TextArea FileListBox;


    @FXML
    private void switchToSecondary() {
        Stage primaryStage = new Stage();
        Stage terminalStage = (Stage) returnBtn.getScene().getWindow();
        try {

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("secondary.fxml"));
            Parent root = loader.load();
            Scene scene = new Scene(root, 640, 480);
            primaryStage.setScene(scene);
            primaryStage.setTitle("Show Users");
            primaryStage.show();
            terminalStage.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void fileCreateBtnHandler(ActionEvent event) {
        try {
            Scanner reader = new Scanner(System.in);
            boolean success = false;

            String dir = "fileDirectory/";

            // Creating new directory in Java, if it doesn't exists
            File directory = new File(dir);
            if (directory.exists()) {
                System.out.println("Directory already exists ...");

            } else {
                System.out.println("Directory not exists, creating now");

                success = directory.mkdir();
                if (success) {
                    System.out.printf("Successfully created new directory : %s%n", dir);
                } else {
                    System.out.printf("Failed to create new directory: %s%n", dir);
                }
            }

            File myObj = new File(dir + fileNameBox.getText());
            if (myObj.createNewFile()) {
                System.out.println("File created: " + myObj.getName());
                FileWriter fWrite = new FileWriter(myObj);
                fWrite.write(fileContentsBox.getText());
                fWrite.close();
                dialogue("New file created", "New file created by " + fileNameBox.getScene().getWindow().getUserData().toString());
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        ShowFiles();
    }
    
    @FXML
    private void ShowFiles()
    {
        FileListBox.setText(Terminal.RunCommand("tree"));
    }

    @FXML
    private void fileDeleteBtnHandler(ActionEvent event) 
    {
        File myObj = new File("fileDirectory/" + fileNameBox.getText());
        if (myObj.delete()) {
            System.out.println("File deleted: " + myObj.getName());
        } else {
            System.out.println("File doesn't exist.");
        }
        ShowFiles();
    }

    @FXML
    private void fileUpdateBtnHandler(ActionEvent event) {
        try {
            FileWriter myObj = new FileWriter(fileNameBox.getText());
            myObj.write(fileContentsBox.getText());
            myObj.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
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


    /**
     * @param args the command line arguments
     */
}
