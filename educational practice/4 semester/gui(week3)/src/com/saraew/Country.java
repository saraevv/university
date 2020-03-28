package com.saraew;

import javax.swing.*;
import java.io.IOException;

public class Country {
    private String name;
    private String capital;
    private ImageIcon image;
    private String description;
    private int price;

    public Country() {}

    public Country(String name, String capital, String imagePath, String description, int price) {
        this.name = name;
        this.capital = capital;
        this.image = new ImageIcon(imagePath);
        this.description = description;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCapital() {
        return capital;
    }

    public void setCapital(String capital) {
        this.capital = capital;
    }

    public ImageIcon getImage() {
        return image;
    }

    public void setImage(ImageIcon image) {
        this.image = image;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return name;
    }
}
