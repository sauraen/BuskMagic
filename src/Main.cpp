/*
* BuskMagic - Live lighting control system
* Copyright (C) 2019 Sauraen
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "JuceHeader.h"
#include "Common.h"

#include "MainWindow.h"

class BuskMagicApplication  : public JUCEApplication {
public:
    BuskMagicApplication() {}

    const String getApplicationName() override    { return "BuskMagic"; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override    { return false; }

    void initialise (const String& commandLine) override {
        ignoreUnused(commandLine); //TODO
        mainWindow.reset(new MainWindow());
    }
    void shutdown() override {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override {
        mainWindow->requestedQuit();
    }
    void anotherInstanceStarted (const String& commandLine) override {
        ignoreUnused(commandLine); //TODO
        WarningBox("This text should never appear. Shoutouts to <insert favorite YouTuber here>");
    }
private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (BuskMagicApplication)
