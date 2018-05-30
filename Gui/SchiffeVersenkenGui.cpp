// Class to setup the GUI

/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
					Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen	(n.westhausen@web.de)
*/

#include "SchiffeVersenkenGui.h"
#include "ui_SchiffeVersenkenGui.h"




SchiffeVersenkenGui::SchiffeVersenkenGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SchiffeVersenkenGui)
{
	
	
    ui->setupUi(this);
    set_bandpass_range();
	set_Messenger_conections();
	setControlsDisabled();
}



// set min and max based on the sample rate
void SchiffeVersenkenGui::set_bandpass_range(void)
{
    ui->spinBox_1L_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_2L_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_3L_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_1R_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_2R_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_3R_bandpass_showF1->setRange(lower_freq_bandpass, upper_freq_bandpass);

    ui->spinBox_1L_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_2L_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_3L_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_1R_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_2R_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);
    ui->spinBox_3R_bandpass_showF2->setRange(lower_freq_bandpass, upper_freq_bandpass);

    ui->horizontalSlider_1L_bandpass_setF1->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_2L_bandpass_setF1->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_3L_bandpass_setF1->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_1R_bandpass_setF1->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_2R_bandpass_setF1->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_3R_bandpass_setF1->setRange(1, upper_freq_bandpass);

    ui->horizontalSlider_1L_bandpass_setF2->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_2L_bandpass_setF2->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_3L_bandpass_setF2->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_1R_bandpass_setF2->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_2R_bandpass_setF2->setRange(1, upper_freq_bandpass);
    ui->horizontalSlider_3R_bandpass_setF2->setRange(1, upper_freq_bandpass);

    ui->spinBox_1L_bandpass_showF2->setValue(upper_freq_bandpass);
    ui->spinBox_2L_bandpass_showF2->setValue(upper_freq_bandpass);
    ui->spinBox_3L_bandpass_showF2->setValue(upper_freq_bandpass);
    ui->spinBox_1R_bandpass_showF2->setValue(upper_freq_bandpass);
    ui->spinBox_2R_bandpass_showF2->setValue(upper_freq_bandpass);
    ui->spinBox_3R_bandpass_showF2->setValue(upper_freq_bandpass);

    ui->horizontalSlider_1L_bandpass_setF2->setValue(upper_freq_bandpass);
    ui->horizontalSlider_2L_bandpass_setF2->setValue(upper_freq_bandpass);
    ui->horizontalSlider_3L_bandpass_setF2->setValue(upper_freq_bandpass);
    ui->horizontalSlider_1R_bandpass_setF2->setValue(upper_freq_bandpass);
    ui->horizontalSlider_2R_bandpass_setF2->setValue(upper_freq_bandpass);
    ui->horizontalSlider_3R_bandpass_setF2->setValue(upper_freq_bandpass);
}

void SchiffeVersenkenGui::set_Messenger_conections()
{
	// Server
	connect(ui->pushButton_connectGui, SIGNAL(clicked()), this, SLOT(conect_to_server()));

	// noise check box
	connect(ui->comboBox_noise_1L_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_1L_name(int)));
	connect(ui->comboBox_noise_2L_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_2L_name(int)));
	connect(ui->comboBox_noise_3L_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_3L_name(int)));
	connect(ui->comboBox_noise_1R_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_1R_name(int)));
	connect(ui->comboBox_noise_2R_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_2R_name(int)));
	connect(ui->comboBox_noise_3R_name, SIGNAL(currentIndexChanged(int)), this, SLOT(conectMesseging_comboBox_noise_3R_name(int)));

	// noise gain
	connect(ui->verticalSlider_1L_noise_Gain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_1L_noise_Gain(int)));
	connect(ui->verticalSlider_2L_noise_Gain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_2L_noise_Gain(int)));
	connect(ui->verticalSlider_3L_noise_Gain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_3L_noise_Gain(int)));
	connect(ui->verticalSlider_1R_noise_setGain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_1R_noise_Gain(int)));
	connect(ui->verticalSlider_2R_noise_setGain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_2R_noise_Gain(int)));
	connect(ui->verticalSlider_3R_noise_setGain, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_verticalSlider_3R_noise_Gain(int)));

	// Bandpass F1 and F2
	connect(ui->horizontalSlider_1L_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_1L_bandpass_setF1(int)));
	connect(ui->horizontalSlider_1L_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_1L_bandpass_setF2(int)));
	connect(ui->horizontalSlider_2L_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_2L_bandpass_setF1(int)));
	connect(ui->horizontalSlider_2L_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_2L_bandpass_setF2(int)));
	connect(ui->horizontalSlider_3L_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_3L_bandpass_setF1(int)));
	connect(ui->horizontalSlider_3L_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_3L_bandpass_setF2(int)));
	connect(ui->horizontalSlider_1R_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_1R_bandpass_setF1(int)));
	connect(ui->horizontalSlider_1R_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_1R_bandpass_setF2(int)));
	connect(ui->horizontalSlider_2R_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_2R_bandpass_setF1(int)));
	connect(ui->horizontalSlider_2R_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_2R_bandpass_setF2(int)));
	connect(ui->horizontalSlider_3R_bandpass_setF1, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_3R_bandpass_setF1(int)));
	connect(ui->horizontalSlider_3R_bandpass_setF2, SIGNAL(valueChanged(int)), this, SLOT(conectMesseging_horizontalSlider_3R_bandpass_setF2(int)));

	// distortion Combobox
	connect(ui->comboBox_distortion_1L_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_1L_characteristic(int)));
	connect(ui->comboBox_distortion_2L_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_2L_characteristic(int)));
	connect(ui->comboBox_distortion_3L_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_3L_characteristic(int)));
	connect(ui->comboBox_distortion_1R_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_1R_characteristic(int)));
	connect(ui->comboBox_distortion_2R_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_2R_characteristic(int)));
	connect(ui->comboBox_distortion_3R_characteristic, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMesseging_comboBox_distortion_3R_characteristic(int)));
	// distortion Slider
	connect(ui->verticalSlider_1L_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_1L_distortion_setOverdrive(int)));
	connect(ui->verticalSlider_2L_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_2L_distortion_setOverdrive(int)));
	connect(ui->verticalSlider_3L_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_3L_distortion_setOverdrive(int)));
	connect(ui->verticalSlider_1R_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_1R_distortion_setOverdrive(int)));
	connect(ui->verticalSlider_2R_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_2R_distortion_setOverdrive(int)));
	connect(ui->verticalSlider_3R_distortion_setOverdrive, SIGNAL(valueChanged(int)), this, SLOT(connectMesseging_verticalSlider_3R_distortion_setOverdrive(int)));

	// reverb Combobox
	connect(ui->comboBox_1L_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_1L_reverb_selection(int)));
	connect(ui->comboBox_2L_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_2L_reverb_selection(int)));
	connect(ui->comboBox_3L_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_3L_reverb_selection(int)));
	connect(ui->comboBox_1R_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_1R_reverb_selection(int)));
	connect(ui->comboBox_2R_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_2R_reverb_selection(int)));
	connect(ui->comboBox_3R_reverb_selection, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_3R_reverb_selection(int)));
	// reverb Slider (dry-Wet)
	connect(ui->horizontalSlider_1L_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_1L_reverb_mix(int)));
	connect(ui->horizontalSlider_2L_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_2L_reverb_mix(int)));
	connect(ui->horizontalSlider_3L_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_3L_reverb_mix(int)));
	connect(ui->horizontalSlider_1R_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_1R_reverb_mix(int)));
	connect(ui->horizontalSlider_2R_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_2R_reverb_mix(int)));
	connect(ui->horizontalSlider_3R_reverb_mix, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_3R_reverb_mix(int)));
	// reverb Slider (Tau60)
	connect(ui->horizontalSlider_1L_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_1L_reverb_tau60(int)));
	connect(ui->horizontalSlider_2L_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_2L_reverb_tau60(int)));
	connect(ui->horizontalSlider_3L_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_3L_reverb_tau60(int)));
	connect(ui->horizontalSlider_1R_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_1R_reverb_tau60(int)));
	connect(ui->horizontalSlider_2R_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_2R_reverb_tau60(int)));
	connect(ui->horizontalSlider_3R_reverb_tau60, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_3R_reverb_tau60(int)));

	// Colorization Combobox
	connect(ui->comboBox_1L_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_1L_colorization(int)));
	connect(ui->comboBox_2L_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_2L_colorization(int)));
	connect(ui->comboBox_3L_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_3L_colorization(int)));
	connect(ui->comboBox_1R_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_1R_colorization(int)));
	connect(ui->comboBox_2R_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_2R_colorization(int)));
	connect(ui->comboBox_3R_colorization, SIGNAL(currentIndexChanged(int)), this, SLOT(connectMessaging_comboBox_3R_colorization(int)));

	// Connect Audio Out Control
	connect(ui->pushButton_client1_pre, SIGNAL(clicked()), this , SLOT(connectMessaging_pushButton_client1_pre()));
	connect(ui->pushButton_client1_post, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_client1_post()));
	connect(ui->pushButton_client1_mute, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_client1_mute()));

	connect(ui->pushButton_client2_pre, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_client2_pre()));
	connect(ui->pushButton_client2_post, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_client2_post()));
	connect(ui->pushButton_client2_mute, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_client2_mute()));

	connect(ui->pushButton_operator_L_pre, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_L_pre()));
	connect(ui->pushButton_operator_L_post, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_L_post()));
	connect(ui->pushButton_operator_L_mute, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_L_mute()));

	connect(ui->pushButton_operator_R_pre, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_R_pre()));
	connect(ui->pushButton_operator_R_post, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_R_post()));
	connect(ui->pushButton_operator_R_mute, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_operator_R_mute()));

	// Recording Control
	connect(ui->pushButton_rec_1, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_rec_1()));
	connect(ui->pushButton_rec_2, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_rec_2()));

	// Effect Control Client 1
	connect(ui->pushButton_effekt_1L, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_1L()));
	connect(ui->pushButton_effekt_2L, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_2L()));
	connect(ui->pushButton_effekt_3L, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_3L()));
	connect(ui->pushButton_return_L, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_return_L()));

	// Effect Control Client 2
	connect(ui->pushButton_effekt_1R, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_1R()));
	connect(ui->pushButton_effekt_2R, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_2R()));
	connect(ui->pushButton_effekt_3R, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_effekt_3R()));
	connect(ui->pushButton_effekt_return_R, SIGNAL(clicked()), this, SLOT(connectMessaging_pushButton_return_R()));

	// Return Control
	connect(ui->verticalSlider_returnL_setGain, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_verticalSlider_returnL_setGain(int)));
	connect(ui->verticalSlider_returnR_setGain, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_verticalSlider_returnR_setGain(int)));
	connect(ui->horizontalSlider_returnL_setDelay, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_returnL_setDelay(int)));
	connect(ui->horizontalSlider_returnR_setDelay, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_horizontalSlider_returnR_setDelay(int)));

	// Operator Gain
	connect(ui->verticalSlider_operator1_setGain, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_verticalSlider_operator1_setGain(int)));
	connect(ui->verticalSlider_operator2_setGain, SIGNAL(valueChanged(int)), this, SLOT(connectMessaging_verticalSlider_operator2_setGain(int)));
}

SchiffeVersenkenGui::~SchiffeVersenkenGui()
{
    delete ui;
	if (messenger_exist == 1)
	{
		delete MessengerGui;
		
	}
}

// function to establish network connection
void SchiffeVersenkenGui::conect_to_server()
{
	bool Value = ui->pushButton_connectGui->isChecked();
	if (Value == true)
	{
		if (messenger_exist == 0)
		{
			int ConectStatus;
			MessengerGui = new GuiMessaging();
			ConectStatus = MessengerGui->connect_to_server(ui->lineEdit_ipAdress->text().toStdString().c_str(), 12344);
			if (ConectStatus == 1)
			{
				setControlsEnabled();
				messenger_exist = 1;
			}
			else
			{
				ui->pushButton_connectGui->setChecked(false);
				delete MessengerGui;
			}
		}
	}
	else
	{
			
		if (messenger_exist == 1)
		{
			delete MessengerGui;
			messenger_exist = 0;
			setControlsDisabled();
		}
	}
}

void SchiffeVersenkenGui::disconect_server()
{
	if (messenger_exist == 1)
	{
		delete MessengerGui;
		messenger_exist = 0;
	}
}

// setting logic for reverb mix
void SchiffeVersenkenGui::on_horizontalSlider_3L_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_3L_reverb_showMix->setValue(double(ui->horizontalSlider_3L_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_3L_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_3L_reverb_mix->setValue(int (ui->doubleSpinBox_3L_reverb_showMix->value()*1000));
}
void SchiffeVersenkenGui::on_horizontalSlider_2L_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_2L_reverb_showMix->setValue(double(ui->horizontalSlider_2L_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_2L_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_2L_reverb_mix->setValue(int (ui->doubleSpinBox_2L_reverb_showMix->value()*1000));
}
void SchiffeVersenkenGui::on_horizontalSlider_1L_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_1L_reverb_showMix->setValue(double(ui->horizontalSlider_1L_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_1L_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_1L_reverb_mix->setValue(int (ui->doubleSpinBox_1L_reverb_showMix->value()*1000));
}
void SchiffeVersenkenGui::on_horizontalSlider_3R_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_3R_reverb_showMix->setValue(double(ui->horizontalSlider_3R_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_3R_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_3R_reverb_mix->setValue(int (ui->doubleSpinBox_3R_reverb_showMix->value()*1000));
}
void SchiffeVersenkenGui::on_horizontalSlider_2R_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_2R_reverb_showMix->setValue(double(ui->horizontalSlider_2R_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_2R_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_2R_reverb_mix->setValue(int (ui->doubleSpinBox_2R_reverb_showMix->value()*1000));
}
void SchiffeVersenkenGui::on_horizontalSlider_1R_reverb_mix_valueChanged()
{
    ui->doubleSpinBox_1R_reverb_showMix->setValue(double(ui->horizontalSlider_1R_reverb_mix->value())/1000);
}
void SchiffeVersenkenGui::on_doubleSpinBox_1R_reverb_showMix_valueChanged()
{
    ui->horizontalSlider_1R_reverb_mix->setValue(int (ui->doubleSpinBox_1R_reverb_showMix->value()*1000));
}



// set logic for bandpass
void SchiffeVersenkenGui::on_horizontalSlider_1L_bandpass_setF1_valueChanged()
{
	ui->spinBox_1L_bandpass_showF1->setValue(ui->horizontalSlider_1L_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_2L_bandpass_setF1_valueChanged()
{
	ui->spinBox_2L_bandpass_showF1->setValue(ui->horizontalSlider_2L_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_3L_bandpass_setF1_valueChanged()
{
	ui->spinBox_3L_bandpass_showF1->setValue(ui->horizontalSlider_3L_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_1R_bandpass_setF1_valueChanged()
{
	ui->spinBox_1R_bandpass_showF1->setValue(ui->horizontalSlider_1R_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_2R_bandpass_setF1_valueChanged()
{
	ui->spinBox_2R_bandpass_showF1->setValue(ui->horizontalSlider_2R_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_3R_bandpass_setF1_valueChanged()
{
	ui->spinBox_3R_bandpass_showF1->setValue(ui->horizontalSlider_3R_bandpass_setF1->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_1L_bandpass_setF2_valueChanged()
{
	ui->spinBox_1L_bandpass_showF2->setValue(ui->horizontalSlider_1L_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_2L_bandpass_setF2_valueChanged()
{
	ui->spinBox_2L_bandpass_showF2->setValue(ui->horizontalSlider_2L_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_3L_bandpass_setF2_valueChanged()
{
	ui->spinBox_3L_bandpass_showF2->setValue(ui->horizontalSlider_3L_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_1R_bandpass_setF2_valueChanged()
{
	ui->spinBox_1R_bandpass_showF2->setValue(ui->horizontalSlider_1R_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_2R_bandpass_setF2_valueChanged()
{
	ui->spinBox_2R_bandpass_showF2->setValue(ui->horizontalSlider_2R_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_horizontalSlider_3R_bandpass_setF2_valueChanged()
{
	ui->spinBox_3R_bandpass_showF2->setValue(ui->horizontalSlider_3R_bandpass_setF2->value());
}

void SchiffeVersenkenGui::on_spinBox_1L_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_1L_bandpass_setF1->setValue(ui->spinBox_1L_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_2L_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_2L_bandpass_setF1->setValue(ui->spinBox_2L_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_3L_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_3L_bandpass_setF1->setValue(ui->spinBox_3L_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_1R_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_1R_bandpass_setF1->setValue(ui->spinBox_1R_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_2R_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_2R_bandpass_setF1->setValue(ui->spinBox_2R_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_3R_bandpass_showF1_valueChanged()
{
	ui->horizontalSlider_3R_bandpass_setF1->setValue(ui->spinBox_3R_bandpass_showF1->value());
}

void SchiffeVersenkenGui::on_spinBox_1L_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_1L_bandpass_setF2->setValue(ui->spinBox_1L_bandpass_showF2->value());
}

void SchiffeVersenkenGui::on_spinBox_2L_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_2L_bandpass_setF2->setValue(ui->spinBox_2L_bandpass_showF2->value());
}

void SchiffeVersenkenGui::on_spinBox_3L_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_3L_bandpass_setF2->setValue(ui->spinBox_3L_bandpass_showF2->value());
}

void SchiffeVersenkenGui::on_spinBox_1R_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_1R_bandpass_setF2->setValue(ui->spinBox_1R_bandpass_showF2->value());
}

void SchiffeVersenkenGui::on_spinBox_2R_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_2R_bandpass_setF2->setValue(ui->spinBox_2R_bandpass_showF2->value());
}

void SchiffeVersenkenGui::on_spinBox_3R_bandpass_showF2_valueChanged()
{
	ui->horizontalSlider_3R_bandpass_setF2->setValue(ui->spinBox_3R_bandpass_showF2->value());
}


// connect to messaging

// noise Combo box
void SchiffeVersenkenGui::conectMesseging_comboBox_noise_1L_name(int Value)
{
	MessengerGui->genMessage(3, L1, NOISE, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_comboBox_noise_2L_name(int Value)
{
	MessengerGui->genMessage(3, L2, NOISE, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_comboBox_noise_3L_name(int Value)
{
	MessengerGui->genMessage(3, L3, NOISE, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_comboBox_noise_1R_name(int Value)
{
	MessengerGui->genMessage(3, R1, NOISE, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_comboBox_noise_2R_name(int Value)
{
	MessengerGui->genMessage(3, R2, NOISE, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_comboBox_noise_3R_name(int Value)
{
	MessengerGui->genMessage(3, R3, NOISE, 1, Value);
}

// Noise gain
void SchiffeVersenkenGui::conectMesseging_verticalSlider_1L_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, L1, NOISE, 2, Value);
}
void SchiffeVersenkenGui::conectMesseging_verticalSlider_2L_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, L2, NOISE, 2, Value);
}
void SchiffeVersenkenGui::conectMesseging_verticalSlider_3L_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, L3, NOISE, 2, Value);
}
void SchiffeVersenkenGui::conectMesseging_verticalSlider_1R_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, R1, NOISE, 2, Value);
}
void SchiffeVersenkenGui::conectMesseging_verticalSlider_2R_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, R2, NOISE, 2, Value);
}
void SchiffeVersenkenGui::conectMesseging_verticalSlider_3R_noise_Gain(int Value)
{
	MessengerGui->genMessage(3, R3, NOISE, 2, Value);
}


// Bandpass F1 and F2
void SchiffeVersenkenGui::conectMesseging_horizontalSlider_1L_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, L1, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_1L_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, L1, BANDPASS, 2, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_2L_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, L2, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_2L_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, L2, BANDPASS, 2, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_3L_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, L3, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_3L_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, L3, BANDPASS, 2, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_1R_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, R1, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_1R_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, R1, BANDPASS, 2, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_2R_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, R2, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_2R_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, R2, BANDPASS, 2, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_3R_bandpass_setF1(int Value)
{
	MessengerGui->genMessage(3, R3, BANDPASS, 1, Value);
}

void SchiffeVersenkenGui::conectMesseging_horizontalSlider_3R_bandpass_setF2(int Value)
{
	MessengerGui->genMessage(3, R3, BANDPASS, 2, Value);
}


// distortion Combobox
void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_1L_characteristic(int Value)
{
	MessengerGui->genMessage(3, L1, DISTORTION, 1, Value);
}

void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_2L_characteristic(int Value)
{
	MessengerGui->genMessage(3, L2, DISTORTION, 1, Value);
}

void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_3L_characteristic(int Value)
{
	MessengerGui->genMessage(3, L3, DISTORTION, 1, Value);
}

void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_1R_characteristic(int Value)
{
	MessengerGui->genMessage(3, R1, DISTORTION, 1, Value);
}

void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_2R_characteristic(int Value)
{
	MessengerGui->genMessage(3, R2, DISTORTION, 1, Value);
}

void SchiffeVersenkenGui::connectMesseging_comboBox_distortion_3R_characteristic(int Value)
{
	MessengerGui->genMessage(3, R3, DISTORTION, 1, Value);
}

// distortion slider
void SchiffeVersenkenGui::connectMesseging_verticalSlider_1L_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, L1, DISTORTION, 2, Value);
}

void SchiffeVersenkenGui::connectMesseging_verticalSlider_2L_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, L2, DISTORTION, 2, Value);
}

void SchiffeVersenkenGui::connectMesseging_verticalSlider_3L_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, L3, DISTORTION, 2, Value);
}

void SchiffeVersenkenGui::connectMesseging_verticalSlider_1R_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, R1, DISTORTION, 2, Value);
}

void SchiffeVersenkenGui::connectMesseging_verticalSlider_2R_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, R2, DISTORTION, 2, Value);
}

void SchiffeVersenkenGui::connectMesseging_verticalSlider_3R_distortion_setOverdrive(int Value)
{
	MessengerGui->genMessage(3, R3, DISTORTION, 2, Value);
}

// reverb Combobox
void SchiffeVersenkenGui::connectMessaging_comboBox_1L_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, L1, REVERB, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_2L_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, L2, REVERB, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_3L_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, L3, REVERB, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_1R_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, R1, REVERB, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_2R_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, R2, REVERB, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_3R_reverb_selection(int Value)
{
	MessengerGui->genMessage(3, R3, REVERB, 1, Value);
}

// Reverb Slider (dry-wet)
void SchiffeVersenkenGui::connectMessaging_horizontalSlider_1L_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, L1, REVERB, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_2L_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, L2, REVERB, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_3L_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, L3, REVERB, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_1R_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, R1, REVERB, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_2R_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, R2, REVERB, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_3R_reverb_mix(int Value)
{
	MessengerGui->genMessage(3, R3, REVERB, 2, Value);
}

//Reverb Slider (Tau60)
void SchiffeVersenkenGui::connectMessaging_horizontalSlider_1L_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, L1, REVERB, 3, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_2L_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, L2, REVERB, 3, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_3L_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, L3, REVERB, 3, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_1R_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, R1, REVERB, 3, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_2R_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, R2, REVERB, 3, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_3R_reverb_tau60(int Value)
{
	MessengerGui->genMessage(3, R3, REVERB, 3, Value);
}

//Colorization Combobox
void SchiffeVersenkenGui::connectMessaging_comboBox_1L_colorization(int Value)
{
	MessengerGui->genMessage(3, L1, COLORIZATION, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_2L_colorization(int Value)
{
	MessengerGui->genMessage(3, L2, COLORIZATION, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_3L_colorization(int Value)
{
	MessengerGui->genMessage(3, L3, COLORIZATION, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_1R_colorization(int Value)
{
	MessengerGui->genMessage(3, R1, COLORIZATION, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_2R_colorization(int Value)
{
	MessengerGui->genMessage(3, R2, COLORIZATION, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_comboBox_3R_colorization(int Value)
{
	MessengerGui->genMessage(3, R3, COLORIZATION, 1, Value);
}

// Connect Audio Out Control
void SchiffeVersenkenGui::connectMessaging_pushButton_client1_pre()
{
	if (ui->pushButton_client1_pre->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 1, 1);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_client1_post()
{
	if (ui->pushButton_client1_post->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 1, 2);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_client1_mute()
{
	if (ui->pushButton_client1_mute->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 1, 0);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_client2_pre()
{
	if (ui->pushButton_client2_pre->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 2, 1);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_client2_post()
{
	if (ui->pushButton_client2_post->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 2, 2);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_client2_mute()
{
	if (ui->pushButton_client2_mute->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(1, 2, 0);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_L_pre()
{
	if (ui->pushButton_operator_L_pre->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 1, 1);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_L_post()
{
	if (ui->pushButton_operator_L_post->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 1, 2);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_L_mute()
{
	if (ui->pushButton_operator_L_mute->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 1, 0);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_R_pre()
{
	if (ui->pushButton_operator_R_pre->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 2, 1);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_R_post()
{
	if (ui->pushButton_operator_R_post->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 2, 2);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_operator_R_mute()
{
	if (ui->pushButton_operator_R_mute->isChecked())
	{
		MessengerGui->genMessage_setAudioOut(0, 2, 0);
	}
}

// Recording Control
void SchiffeVersenkenGui::connectMessaging_pushButton_rec_1()
{
	if (ui->pushButton_rec_1->isChecked())
	{
		if (std::string("").compare(ui->lineEdit_name_1->text().toStdString())== 0)
		{
			ui->pushButton_rec_1->setChecked(false);
		}
		else
		{
			MessengerGui->genMessage_setRecording(1, 1, ui->lineEdit_name_1->text().toStdString());
		}
	}
	else
	{
		MessengerGui->genMessage_setRecording(1, 0);
	}
}

void SchiffeVersenkenGui::connectMessaging_pushButton_rec_2()
{
	if (ui->pushButton_rec_2->isChecked())
	{
		if (std::string("").compare(ui->lineEdit_name_2->text().toStdString()) == 0)
		{
			ui->pushButton_rec_2->setChecked(false);
		}
		else
		{
			MessengerGui->genMessage_setRecording(2, 1, ui->lineEdit_name_2->text().toStdString());
		}
	}
	else
	{
		MessengerGui->genMessage_setRecording(2, 0);
	}
}

// Effect Control Client 1
void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_1L()
{
	if (ui->pushButton_effekt_1L->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(L1, ui->comboBox_1L_setEffect->currentIndex()*10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(L1, ui->comboBox_1L_setEffect->currentIndex()*10, 0);

}

void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_2L()
{
	if (ui->pushButton_effekt_2L->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(L2, ui->comboBox_2L_setEffekt->currentIndex() * 10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(L2, ui->comboBox_2L_setEffekt->currentIndex() * 10, 0);
}

void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_3L()
{
	if (ui->pushButton_effekt_3L->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(L3, ui->comboBox_3L_setEffekt->currentIndex() * 10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(L3, ui->comboBox_3L_setEffekt->currentIndex() * 10, 0);
}

void SchiffeVersenkenGui::connectMessaging_pushButton_return_L()
{
	if (ui->pushButton_return_L->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(ReturnL, ReturnL, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(ReturnL, ReturnL, 0);
}

// Effect Control Client 2
void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_1R()
{
	if (ui->pushButton_effekt_1R->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(R1, ui->comboBox_1R_setEffect->currentIndex() * 10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(R1, ui->comboBox_1R_setEffect->currentIndex() * 10, 0);
}

void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_2R()
{
	if (ui->pushButton_effekt_2R->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(R2, ui->comboBox_2R_setEffect->currentIndex() * 10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(R2, ui->comboBox_2R_setEffect->currentIndex() * 10, 0);
}

void SchiffeVersenkenGui::connectMessaging_pushButton_effekt_3R()
{
	if (ui->pushButton_effekt_3R->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(R3, ui->comboBox_3R_setEffect->currentIndex() * 10, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(R3, ui->comboBox_3R_setEffect->currentIndex() * 10, 0);
}

void SchiffeVersenkenGui::connectMessaging_pushButton_return_R()
{
	if (ui->pushButton_effekt_return_R->isChecked())
	{
		MessengerGui->genMessage_setEffectStatus(ReturnR, ReturnR, 1);
	}
	else MessengerGui->genMessage_setEffectStatus(ReturnR, ReturnR, 0);
}

// Return Control
void SchiffeVersenkenGui::connectMessaging_verticalSlider_returnL_setGain(int Value)
{
	MessengerGui->genMessage(3, ReturnL, ReturnL, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_returnL_setDelay(int Value)
{
	MessengerGui->genMessage(3, ReturnL, ReturnL, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_verticalSlider_returnR_setGain(int Value)
{
	MessengerGui->genMessage(3, ReturnR, ReturnR, 1, Value);
}

void SchiffeVersenkenGui::connectMessaging_horizontalSlider_returnR_setDelay(int Value)
{
	MessengerGui->genMessage(3, ReturnR, ReturnR, 2, Value);
}

void SchiffeVersenkenGui::connectMessaging_verticalSlider_operator1_setGain(int Value)
{
	MessengerGui->genMessage_setGainOperator(1, Value);
}

void SchiffeVersenkenGui::connectMessaging_verticalSlider_operator2_setGain(int Value)
{
	MessengerGui->genMessage_setGainOperator(2, Value);
}


// disable all controls
void SchiffeVersenkenGui::setControlsDisabled()
{
	setDisabledRecursiv(ui->controls_client_1, false);
	setDisabledRecursiv(ui->controls_client_2, false);
	setDisabledRecursiv(ui->Audio_out_left, false);
	setDisabledRecursiv(ui->Audio_out_right, false);
	ui->verticalSlider_operator1_setGain->setEnabled(false);
	ui->verticalSlider_operator2_setGain->setEnabled(false);
}

void SchiffeVersenkenGui::setDisabledRecursiv(QLayout *layoutDings, bool action)
{
	for (int i = 0; i < layoutDings->count(); ++i)
	{
		QWidget *widget = layoutDings->itemAt(i)->widget();
		if (widget != NULL)
		{
			widget->setEnabled(action);
		}
	}
}
// enable all controls
void SchiffeVersenkenGui::setControlsEnabled()
{
	setDisabledRecursiv(ui->controls_client_1, true);
	setDisabledRecursiv(ui->controls_client_2, true);
	setDisabledRecursiv(ui->Audio_out_left, true);
	setDisabledRecursiv(ui->Audio_out_right, true);
	ui->verticalSlider_operator1_setGain->setEnabled(true);
	ui->verticalSlider_operator2_setGain->setEnabled(true);
}
