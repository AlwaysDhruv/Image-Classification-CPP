# Image Classification - CNNs Implement From Scratch Using C++

A from-scratch implementation of a Convolutional Neural Network (CNN) for image classification, written in C++ with Python for preprocessing database with proper file structure.

![Architecture Diagram](https://github.com/user-attachments/assets/5eec279a-eaca-455c-a056-3fca3d46483e)

## 📜 Table of Contents

- [About The Project](#about-the-project)
- [🤖 Architecture](#architecture)
- [🚀 Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
  - [Running the Application](#running-the-application)
- [🔧 Usage](#usage)
  - [Training](#training)
  - [Prediction](#prediction)
- [📁 Project Structure](#project-structure)
- [🐍 Python Version](#python-version)

## About The Project

This project is a complete, from-scratch implementation of a Convolutional Neural Network (CNN) in C++. It is designed to be a learning tool for understanding the inner workings of CNNs without relying on high-level deep learning libraries.

### Features

- **Custom CNN Implementation:** All neural network components are built from the ground up in C++.
- **Convolutional Layer:** Extracts features from images using filters.
- **Activation Functions:** Implements ReLU and Softmax.
- **Max Pooling:** Reduces the spatial dimensions of the feature maps.
- **Dense Layer:** A fully connected layer for classification.
- **Backpropagation:** Custom implementation for training the network.
- **Python Preprocessing:** Uses Python and the Pillow library to preprocess images.

## 🤖 Architecture

The CNN architecture is composed of the following layers:

1.  **Input Image** (64x64 grayscale)
2.  **Convolutional Layer** with custom filters.
3.  **ReLU Activation Function** to introduce non-linearity.
4.  **Max Pooling Layer** to downsample the feature maps.
5.  **Flatten Layer** to convert the 2D feature maps into a 1D vector.
6.  **Dense (Fully Connected) Layer** to perform classification.
7.  **Softmax Activation Function** to output class probabilities.

## 🚀 Getting Started

This project is designed to run on **Windows** due to its use of the Windows API for file and folder operations.

### Prerequisites

- A C++ compiler that supports C++17 (e.g., MinGW g++ or Visual C++).
- Python 3.x.
- The Pillow Python library.

You can install Pillow using pip:
```bash
pip install Pillow
```

### Building the Project

1.  Make sure you have a C++ compiler (like MinGW g++) and Python installed and configured in your system's PATH.
2.  Open a terminal or command prompt in the root directory of the project.
3.  Compile the C++ code using the following command:

```bash
g++ source/main.cpp -o ImageClassification.exe -lcomdlg32 -lshell32 -lole32 -static-libgcc -static-libstdc++ -std=c++17
```
This will create an `ImageClassification.exe` executable in the root directory.

### Running the Application

Run the compiled application from the terminal:

```bash
./ImageClassification.exe
```

## 🔧 Usage

The application provides a command-line menu with the following options:

1.  **Train On New Dataset:** Train the model on a new set of images.
2.  **Predict Image:** Use the trained model to predict the class of a single image.
3.  **Clear Screen:** Clears the console.
4.  **Exit:** Exits the application.

### Training

1.  Select option `1` from the menu.
2.  A folder selection dialog will appear. Choose the root folder of your dataset.
3.  The dataset must be organized into subdirectories, where each subdirectory's name corresponds to a class label. For example:
    ```
    Test_Data/
    ├── axethrowing/
    │   ├── 1.jpg
    │   └── 2.jpg
    └── balancebeam/
        ├── 1.jpg
        └── 2.jpg
    ```
4.  The application will then ask for the number of training epochs. Enter a number and press Enter.
5.  The model will start training. The preprocessing scripts will create a `pixels` directory with `.txt` files containing the normalized pixel data.

### Prediction

1.  After training the model, you can predict a single image by selecting option `2`.
2.  The application will prompt you for the path to an image file.
3.  Enter the full path to the image and press Enter.
4.  The model will output the predicted class for the image.
5.  A `pixel` directory will be created during this process and should be automatically deleted afterward.

## 📁 Project Structure

```
.
├── source/                  # C++ and Python source code
│   ├── Backprogation_Layer/
│   ├── Convolution_Layer/
│   ├── Dence_Layer/
│   ├── Preprocessing/
│   └── WeigthsBiases/
├── Test_Data/               # Sample data for testing
└── ...
```

## 🐍 Python Version

A pure Python version of this project is also available. You can find it here:
[Image-Classification-PY](https://github.com/AlwaysDhruv/Image-Classification-PY)
