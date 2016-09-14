// ----------------------------- VIEW FUNCITONS -----------------------------//
//   Comment:
//    The following functions represent one view.
//     Each view - function can have the following steps:
//       1.  Clear the screen
//       2.  Print out the new view
//       3.  Ask for user key-input to globalKey;
//       4.  Make a descision based on that input
//
//    To make the game appear consistent across all views we have to     
//     standardize the width and height of each view.
//     The window object should make sure that width and high are consistent
//     across views. 
//
//   ASCII - resolution:  70(0-69 +1 newline character) x 20 lines (0-19).
//
 

// ----- View functions ----- //
void openingView();
void travelView(string fromLocation, string toLocation, int length);
void mainMenuView();