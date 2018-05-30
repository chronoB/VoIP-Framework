/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
Nils L. Westhausen	(n.westhausen@web.de)
*/

// class to setup the GUI

#ifndef SCHIFFEVERSENKENGUI_H
#define SCHIFFEVERSENKENGUI_H

#include <QMainWindow>
#include <QObject>
#include "audio_parameter.h"
#include "GuiMessaging.h"
#include <QTextCodec>



namespace Ui {
class SchiffeVersenkenGui;
}

class SchiffeVersenkenGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit SchiffeVersenkenGui(QWidget *parent = 0);
    ~SchiffeVersenkenGui();

	private slots:
	// Conect to server
	void conect_to_server();
	
    void disconect_server(void);
    // function for logic in reverb_mix
    void on_horizontalSlider_3L_reverb_mix_valueChanged();
    void on_doubleSpinBox_3L_reverb_showMix_valueChanged();
    void on_horizontalSlider_2L_reverb_mix_valueChanged();
    void on_doubleSpinBox_2L_reverb_showMix_valueChanged();
    void on_horizontalSlider_1L_reverb_mix_valueChanged();
    void on_doubleSpinBox_1L_reverb_showMix_valueChanged();
    void on_horizontalSlider_3R_reverb_mix_valueChanged();
    void on_doubleSpinBox_3R_reverb_showMix_valueChanged();
    void on_horizontalSlider_2R_reverb_mix_valueChanged();
    void on_doubleSpinBox_2R_reverb_showMix_valueChanged();
    void on_horizontalSlider_1R_reverb_mix_valueChanged();
    void on_doubleSpinBox_1R_reverb_showMix_valueChanged();

	// conection to messeging
	// Noise Combobox
	void conectMesseging_comboBox_noise_1L_name(int Value);
	void conectMesseging_comboBox_noise_2L_name(int Value);
	void conectMesseging_comboBox_noise_3L_name(int Value);
	void conectMesseging_comboBox_noise_1R_name(int Value);
	void conectMesseging_comboBox_noise_2R_name(int Value);
	void conectMesseging_comboBox_noise_3R_name(int Value);
	// Noise Gain
	void conectMesseging_verticalSlider_1L_noise_Gain(int Value);
	void conectMesseging_verticalSlider_2L_noise_Gain(int Value);
	void conectMesseging_verticalSlider_3L_noise_Gain(int Value);
	void conectMesseging_verticalSlider_1R_noise_Gain(int Value);
	void conectMesseging_verticalSlider_2R_noise_Gain(int Value);
	void conectMesseging_verticalSlider_3R_noise_Gain(int Value);

	// Bandpass
	void conectMesseging_horizontalSlider_1L_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_1L_bandpass_setF2(int);
	void conectMesseging_horizontalSlider_2L_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_2L_bandpass_setF2(int);
	void conectMesseging_horizontalSlider_3L_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_3L_bandpass_setF2(int);
	void conectMesseging_horizontalSlider_1R_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_1R_bandpass_setF2(int);
	void conectMesseging_horizontalSlider_2R_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_2R_bandpass_setF2(int);
	void conectMesseging_horizontalSlider_3R_bandpass_setF1(int);
	void conectMesseging_horizontalSlider_3R_bandpass_setF2(int);

	// distortion Combobox
	void connectMesseging_comboBox_distortion_1L_characteristic(int Value);
	void connectMesseging_comboBox_distortion_2L_characteristic(int Value);
	void connectMesseging_comboBox_distortion_3L_characteristic(int Value);
	void connectMesseging_comboBox_distortion_1R_characteristic(int Value);
	void connectMesseging_comboBox_distortion_2R_characteristic(int Value);
	void connectMesseging_comboBox_distortion_3R_characteristic(int Value);
	// Verzerung Slider
	void connectMesseging_verticalSlider_1L_distortion_setOverdrive(int Value);
	void connectMesseging_verticalSlider_2L_distortion_setOverdrive(int Value);
	void connectMesseging_verticalSlider_3L_distortion_setOverdrive(int Value);
	void connectMesseging_verticalSlider_1R_distortion_setOverdrive(int Value);
	void connectMesseging_verticalSlider_2R_distortion_setOverdrive(int Value);
	void connectMesseging_verticalSlider_3R_distortion_setOverdrive(int Value);

	// Reverb Combobox
	void connectMessaging_comboBox_1L_reverb_selection(int Value);
	void connectMessaging_comboBox_2L_reverb_selection(int Value);
	void connectMessaging_comboBox_3L_reverb_selection(int Value);
	void connectMessaging_comboBox_1R_reverb_selection(int Value);
	void connectMessaging_comboBox_2R_reverb_selection(int Value);
	void connectMessaging_comboBox_3R_reverb_selection(int Value);
	// Reverb Slider (dry-wet)
	void connectMessaging_horizontalSlider_1L_reverb_mix(int Value);
	void connectMessaging_horizontalSlider_2L_reverb_mix(int Value);
	void connectMessaging_horizontalSlider_3L_reverb_mix(int Value);
	void connectMessaging_horizontalSlider_1R_reverb_mix(int Value);
	void connectMessaging_horizontalSlider_2R_reverb_mix(int Value);
	void connectMessaging_horizontalSlider_3R_reverb_mix(int Value);
	// Reverb Slider (Tau60)
	void connectMessaging_horizontalSlider_1L_reverb_tau60(int Value);
	void connectMessaging_horizontalSlider_2L_reverb_tau60(int Value);
	void connectMessaging_horizontalSlider_3L_reverb_tau60(int Value);
	void connectMessaging_horizontalSlider_1R_reverb_tau60(int Value);
	void connectMessaging_horizontalSlider_2R_reverb_tau60(int Value);
	void connectMessaging_horizontalSlider_3R_reverb_tau60(int Value);

	// Reverb Combobox
	void connectMessaging_comboBox_1L_colorization(int Value);
	void connectMessaging_comboBox_2L_colorization(int Value);
	void connectMessaging_comboBox_3L_colorization(int Value);
	void connectMessaging_comboBox_1R_colorization(int Value);
	void connectMessaging_comboBox_2R_colorization(int Value);
	void connectMessaging_comboBox_3R_colorization(int Value);

	// Coonect Audio Out Control
	void connectMessaging_pushButton_client1_pre(void);
	void connectMessaging_pushButton_client1_post(void);
	void connectMessaging_pushButton_client1_mute(void);

	void connectMessaging_pushButton_client2_pre(void);
	void connectMessaging_pushButton_client2_post(void);
	void connectMessaging_pushButton_client2_mute(void);

	void connectMessaging_pushButton_operator_L_pre(void);
	void connectMessaging_pushButton_operator_L_post(void);
	void connectMessaging_pushButton_operator_L_mute(void);

	void connectMessaging_pushButton_operator_R_pre(void);
	void connectMessaging_pushButton_operator_R_post(void);
	void connectMessaging_pushButton_operator_R_mute(void);

	// Recording Control
	void connectMessaging_pushButton_rec_1(void);
	void connectMessaging_pushButton_rec_2(void);

	// Effect Control Client 1
	void connectMessaging_pushButton_effekt_1L(void);
	void connectMessaging_pushButton_effekt_2L(void);
	void connectMessaging_pushButton_effekt_3L(void);
	void connectMessaging_pushButton_return_L(void);

	// Effect Control Client 2
	void connectMessaging_pushButton_effekt_1R(void);
	void connectMessaging_pushButton_effekt_2R(void);
	void connectMessaging_pushButton_effekt_3R(void);
	void connectMessaging_pushButton_return_R(void);

	// Return Control
	void connectMessaging_verticalSlider_returnL_setGain(int Value);
	void connectMessaging_horizontalSlider_returnL_setDelay(int Value);
	void connectMessaging_verticalSlider_returnR_setGain(int Value);
	void connectMessaging_horizontalSlider_returnR_setDelay(int Value);
	
	// Gain Operator
	void connectMessaging_verticalSlider_operator1_setGain(int Value);
	void connectMessaging_verticalSlider_operator2_setGain(int Value);

    // logic for bandpass
    void on_horizontalSlider_1L_bandpass_setF1_valueChanged();
    void on_horizontalSlider_2L_bandpass_setF1_valueChanged();
    void on_horizontalSlider_3L_bandpass_setF1_valueChanged();
    void on_horizontalSlider_1R_bandpass_setF1_valueChanged();
    void on_horizontalSlider_2R_bandpass_setF1_valueChanged();
    void on_horizontalSlider_3R_bandpass_setF1_valueChanged();

    void on_horizontalSlider_1L_bandpass_setF2_valueChanged();
    void on_horizontalSlider_2L_bandpass_setF2_valueChanged();
    void on_horizontalSlider_3L_bandpass_setF2_valueChanged();
    void on_horizontalSlider_1R_bandpass_setF2_valueChanged();
    void on_horizontalSlider_2R_bandpass_setF2_valueChanged();
    void on_horizontalSlider_3R_bandpass_setF2_valueChanged();

    void on_spinBox_1L_bandpass_showF1_valueChanged();
    void on_spinBox_2L_bandpass_showF1_valueChanged();
    void on_spinBox_3L_bandpass_showF1_valueChanged();
    void on_spinBox_1R_bandpass_showF1_valueChanged();
    void on_spinBox_2R_bandpass_showF1_valueChanged();
    void on_spinBox_3R_bandpass_showF1_valueChanged();

    void on_spinBox_1L_bandpass_showF2_valueChanged();
    void on_spinBox_2L_bandpass_showF2_valueChanged();
    void on_spinBox_3L_bandpass_showF2_valueChanged();
    void on_spinBox_1R_bandpass_showF2_valueChanged();
    void on_spinBox_2R_bandpass_showF2_valueChanged();
    void on_spinBox_3R_bandpass_showF2_valueChanged();	

private:
    Ui::SchiffeVersenkenGui *ui;
    int lower_freq_bandpass = 5;
    int upper_freq_bandpass = SAMPLE_RATE / 2 -10;
    void set_bandpass_range(void);
	void set_Messenger_conections(void);
	void setControlsDisabled(void);
	void setControlsEnabled(void);
	void setDisabledRecursiv(QLayout *layoutDings, bool action);
	GuiMessaging *MessengerGui;
	const char * Ip_adress;
	int sendPort;
	int messenger_exist = 0;
};

#endif // SCHIFFEVERSENKENGUI_H
