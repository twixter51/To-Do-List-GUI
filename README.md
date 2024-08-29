# To-Do-List-GUI (WxWidgets) 
Uses wxWidgets Library (C++)



# HOW TO SET UP

Please be aware that setting this up in a codespace environment is complex and annoying, you can look up how to do it you will need to install wxWidgets in 
your codespace environment so i'll give you the starting steps:

INSTALL WXWIDGETS: 

1. sudo apt-get update

2. sudo apt-get install libwxgtk3.0-gtk3-dev
 
3. mkdir build

4. cd build

Now you will be using the CMAKELISTS file that I put in here.

5. cmake ..

6. make

7. ./YourExecutableName


# Follow everything above in order, edit the Cmake File and change the names to anything you want. You will encounter an error at the end because theres no way to display the GUI, for that I say use X11 forwarding. Good luck 
# To save yourself a headache
# just download wxWidgets in Visual Studio or any IDE for that matter and have it display from there.



This is my first project, the code may not look that nice (FOR NOW) but please bear with me :).

Since I'm using wxWidgets, this UI is cross-platform, current features include:

-- Add tasks by typing into a search bar

-- Remove tasks by selecting one or many

-- Checks to ensure there are tasks entered

--  priority feature (set priority to any task you like! there are currently 2 forms, yellow (normal priority), red (urgency)

-- prioritize features for better readability, color enhancements, tooltips.

-- remove all tasks button

-- remove all priorities button

-- prompt logic is now better

-- Saving system, saves your data to SavesFile1.txt


# RELEASE v.1
 


# Planned Updates
?????

