**Cloning Steps**

Resources:
- Visual Studio 2022 Community version (ensure the 'Desktop development with C++' and 'Game development with C++' workloads have been preinstalled, if not you can modify your Visual Studio build via 'Visual Studio Installer' to add those packages)
- Git
- directxtk12_desktop_2019 NuGet package
- Microsoft.Windows.CppWinRT NuGet package

Note: The NuGet packages should come preinstalled with the repository, but just in case this README file will cover how to install the packages too.

Steps:
1. In the ControllerUI repository, press the green 'Code' button.
2. Under 'Local' then 'HTTPS', copy the git repo link into the computer's clipboard.
3. Open Visual Studio 2022 on your machine.
4. Under 'Get Started', select 'Clone a repository'.
5. In the 'Repository location' textbox, enter the link that was saved onto the clipboard.
6. Press 'Clone' located on the bottom right corner of the window.
7. Visual Studio will now open the project as an IDE. 
8. Before pressing 'Local Windows Debugger' to run the project, ensure the NuGet packages outlined in the 'Resources' section have been updated to the latest version.
9. To do this, in the top left corner, press 'Project'.
10. Select 'Manage NuGet Packages...'.
11. Under the 'Updates' tab, check 'directxtk12_desktop_2019' and 'Microsoft.Windows.CppWinRT' and confirm the update.
12. A popup window will appear asking for a confirmation that the two packages should be updated, proceed.
13. With the NuGet packages now updated, exit out of the NuGet package manager window and press 'Local Windows Debugger'. Viola!

None of the packages mentioned under 'Resources' appear in my NuGet Package Manager. What do?
1. Take a step back.
2. Breathe in and breathe out.
3. Calm yourself.
4. Click the 'Browse' tab.
5. In the search bar type "directxtk12_desktop_2019".
6. Select the first option available (the package should be authored by Microsoft and have an icon similar to that of a 4-leaf clover).
7. Install.
8. Once done, type "Microsoft.Windows.CppWinRT" into the search bar.
9. Select the option that has a 'Windows 10' logo.
10. Install. Viola! You have both of the packages NuGet packages installed.
