/* Copyright (C) 2014 by Jacob Alexander
 *
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

// ----- Includes -----

// Qt
#include <QFileDialog>
#include <QScrollBar>
#include <QtWidgets>
#include <QDebug>

// Local
#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString strfile;

// ----- Functions -----

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ), ui( new Ui::MainWindow )
{
	ui->setupUi( this );

    strfile = QCoreApplication::applicationDirPath();
	// Connections
    connect( ui->JavaScriptButton, SIGNAL( released() ), this, SLOT( dfuFlashBinary() ) );
    connect( ui->ArduinoButton, SIGNAL(released()), this, SLOT( openArduino() ) );
    connect( ui->ParticleButton, SIGNAL(released()), this, SLOT( openParticle() ) );

	// Only use the included dfu-util
	binaryPath = QFileInfo( QCoreApplication::applicationFilePath() ).dir().absolutePath();
	dfuUtilProcess.setWorkingDirectory( binaryPath );

	// Merge the output channels
	dfuUtilProcess.setProcessChannelMode( QProcess::MergedChannels );
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::dfuFlashBinary()
{

		// Run dfu-util command
    QString jsCmd = QString("openocd -f %1/redbearduo.cfg -c \"program %2/js.bin verify reset exit 0x80c0000\"").arg(strfile).arg(strfile);
    dfuUtilProcess.start( jsCmd );
    // Disable the flash button while command is running
    ui->JavaScriptButton->setDisabled( true );
    ui->ArduinoButton->setDisabled( true );
    ui->ParticleButton->setDisabled( true );
    dfuUtilProcess.waitForFinished();
    dfuUtilProcess.close();

    QString program = "\"/Applications/Espruino Web IDE.app\"";
    openEProcess.start(program);

    //openEProcess.waitForFinished();
    //openEProcess.close();

    QString output1 = tr("Open the Espruino Web IDE");
    ui->dfuResultsTextEdit->append( output1 );

    // Disable the flash button while command is running
    ui->JavaScriptButton->setDisabled( false );
    ui->ArduinoButton->setDisabled( false );
    ui->ParticleButton->setDisabled( false );
}



void MainWindow::openArduino()
{

    QString ArCmd = QString("openocd -f %1/redbearduo.cfg -c \"program %2/Ard_RGB.ino.bin verify reset exit 0x80c0000\"").arg(strfile).arg(strfile);
    dfuUtilProcess.start( ArCmd );
    // Disable the flash button while command is running
    ui->JavaScriptButton->setDisabled( true );
    ui->ArduinoButton->setDisabled( true );
    ui->ParticleButton->setDisabled( true );
    dfuUtilProcess.waitForFinished();
    dfuUtilProcess.close();
    const QString program = "/Applications/Arduino.app";
    openAProcess.start(program);
    QString output = tr("Open the Arduino IDE");
    ui->dfuResultsTextEdit->append( output );

    ui->JavaScriptButton->setDisabled( false );
    ui->ArduinoButton->setDisabled( false );
    ui->ParticleButton->setDisabled( false );
}

void MainWindow::openParticle()
{
    QString cloudCmd = QString("openocd -f %1/redbearduo.cfg -c \"program %2/Particle_Blink.ino.bin verify reset exit 0x80c0000\"").arg(strfile).arg(strfile);
    dfuUtilProcess.start( cloudCmd );
    // Disable the flash button while command is running
    ui->JavaScriptButton->setDisabled( true );
    ui->ArduinoButton->setDisabled( true );
    ui->ParticleButton->setDisabled( true );
    dfuUtilProcess.waitForFinished();
    dfuUtilProcess.close();
    ui->JavaScriptButton->setDisabled( false );
    ui->ArduinoButton->setDisabled( false );
    ui->ParticleButton->setDisabled( false );
    QDesktopServices::openUrl(QUrl("https://build.particle.io/login"));
    QString output = tr("Open the Particle Web IDE");
    ui->dfuResultsTextEdit->append( output );
}
