/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.javafxapplication1;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *
 * @author ntu-user
 */
public class Terminal {

    static String RunCommand(String Command) {
        var processBuilder = new ProcessBuilder();
        try {
            String[] Commands = Command.split(" ");
            if (Commands[0].equals("nano")) {
                try {
                    String[] args = new String[]{"/bin/bash", "-c", "terminator -e 'nano " + Commands[1] + "'"};
                    Process process = new ProcessBuilder(args).start();
                    return "Running nano";
                } catch (ArrayIndexOutOfBoundsException e) {
                    return "Nano requires file parameter";
                }
            } else {
                var process = processBuilder.command(Commands).directory(new File("fileDirectory")).start();
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder builder = new StringBuilder();
                String line = null;

                while ((line = reader.readLine()) != null) {
                    builder.append(line);
                    builder.append(System.getProperty("line.separator"));
                }
                String result = builder.toString();
                process.destroy();
                return result;
            }

        } catch (IOException ex) {
            return ex.toString();
        }

    }
}
