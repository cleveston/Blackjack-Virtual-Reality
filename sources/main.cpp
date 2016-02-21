
#include "Numbers.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "marker_detector.h"

using namespace std;

//Prototypes
void init();
void initGui();
void glui_callback(int control_id);
string convertInt(int number);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle();
void display();

//Default constants
const int INITIAL_MONEY = 100;

//The id of the main window
GLuint main_window;

//The gui window
GLUI * glui_window;

//  variables representing the window size
int window_width = 512;
int window_height = 512;

//Gui buttons
enum buttons
{
	INCREASE_BUTTON,
	DECREASE_BUTTON,
	START_MATCH_BUTTON,
	CONTINUE_BUTTON,
	STOP_BUTTON,
};

//The buttons
GLUI_Button *INCREASE, *DECREASE, *START_MATCH, *STOP, *CONTINUE;

//The labels
GLUI_StaticText *MY_MONEY, *MONEY_BET, *DEALER_CARDS, *DEALER_SCORE, *MY_CARDS, *MY_SCORE, *STATUS;

//States of the Blackjack
enum states{
	NEW_GAME,
	NEW_MATCH,
	SET_BET,
	FIRST_CARDS,
	YOUR_TURN,
	DEALER_TURN,
	LOST,
	WON,
	EVEN,
	WAIT_NEW_MATCH,
	END
};

//The bet value
int bet = 0;

//Control variables
bool yes = false;
bool no = false;

Player *you;
Player *dealer;
Deck *deck;

//Initial state of FSM
states current = NEW_GAME;

// Window.
GLuint wndW;
GLuint wndH;
GLfloat wndAR;

// OpenGL
GLuint tex;						// OpenGL texture id.
GLfloat texAR;					// Texture aspect ratio.
GLfloat nearPlane = 0.01f;		// Near clipping plane distance.
GLfloat farPlane = 100.0f;		// Far clipping plane distance.
Matrix44 projMatrix;			// Projection matrix.

//OpenCV.
cv::VideoCapture cap;
cv::Mat frame;
HWND wndHandle = NULL;

//Camera and markers definitions
CameraCalibration camCalib(725.864f, 725.864f, 319.500f, 239.500f);
MarkerDetector* mrkDetective = NULL;
std::vector<Transformation> transfs;
std::vector<int> mrks;

//Main function
int main(int argc, char **argv)
{
	// Create a marker detector object.
	mrkDetective = new MarkerDetector(camCalib);
	// Configure a video capture object.
	cap.open(2);

	//Try to open the camera
	if (!(cap.isOpened())) { printf("Could not open the camera!\n"); return -1; }

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	main_window = glutCreateWindow("Blackjack Game");
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) { exit(EXIT_FAILURE); }
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	//Init Opencv
	init();

	//Initialize the GUI
	initGui();

	glutMainLoop();

	// Release OpenCV resources.
	cv::destroyAllWindows();
	cap.release();
	frame.release();

	return 0;

}

//OpenGl Projection Matrix
void updateOpenGLProjMatrix(int w, int h)
{
	float fX = camCalib.getIntrinsic().mat[0][0];		// Camera focal length in X axis.
	float fY = camCalib.getIntrinsic().mat[1][1];		// Camera focal length in Y axis.
	float cX = camCalib.getIntrinsic().mat[0][2];		// Camera primary point X.
	float cY = camCalib.getIntrinsic().mat[1][2];		// Camera primary point Y.
	// OpenGL projection matrix 1st column.
	projMatrix.data[0] = 2.0f * fX / float(w);
	projMatrix.data[1] = 0.0f;
	projMatrix.data[2] = 0.0f;
	projMatrix.data[3] = 0.0f;
	// OpenGL projection matrix 2nd column.
	projMatrix.data[4] = 0.0f;
	projMatrix.data[5] = 2.0f * fY / float(h);
	projMatrix.data[6] = 0.0f;
	projMatrix.data[7] = 0.0f;
	// OpenGL projection matrix 3rd column.
	projMatrix.data[8] = (2.0f * cX / float(w)) - 1.0f;
	projMatrix.data[9] = (2.0f * cY / float(h)) - 1.0f;
	projMatrix.data[10] = -(float(farPlane) + float(nearPlane)) / (float(farPlane) - float(nearPlane));
	projMatrix.data[11] = -1.0f;
	// OpenGL projection matrix 4th column.
	projMatrix.data[12] = 0.0f;
	projMatrix.data[13] = 0.0f;
	projMatrix.data[14] = -2.0f * float(farPlane) * float(nearPlane) / (float(farPlane) - float(nearPlane));
	projMatrix.data[15] = 0.0f;
}

//Init function
void init()
{
	// Init shaders and program data.
	shaderVert.type = GL_VERTEX_SHADER;
	shaderVert.readShaderFromFile("../shaders/blackjack.vert");
	shaderFrag.type = GL_FRAGMENT_SHADER;
	shaderFrag.readShaderFromFile("../shaders/blackjack.frag");
	shaderProg.vert = &shaderVert;
	shaderProg.frag = &shaderFrag;
	shaderProg.id = ShaderProgramManager::LoadShaders(shaderProg.vert, shaderProg.frag, NULL);
	// Activate the newly created shader program.
	glUseProgram(shaderProg.id);
	// Retrieve the location of modelview and projection matrices in the shaders.
	locMatrixModel = glGetUniformLocation(shaderProg.id, "model_matrix");
	locMatrixProj = glGetUniformLocation(shaderProg.id, "projection_matrix");
	// Set up the element buffer object (EBO).
	glGenBuffers(NumEBOs, EBOs);

	// EBO NUMBER ZERO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n0VertIdx), n0VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER ONE.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n1VertIdx), n1VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER TWO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n2VertIdx), n2VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER THREE.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n3VertIdx), n3VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER FOUR.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n4VertIdx), n4VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER FIVE.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON5]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n5VertIdx), n5VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER SIX.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON6]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n6VertIdx), n6VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER SEVEN.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON7]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n7VertIdx), n7VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER EIGHT.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON8]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n8VertIdx), n8VertIdx, GL_STATIC_DRAW);
	// EBO NUMBER NINE.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON9]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(n9VertIdx), n9VertIdx, GL_STATIC_DRAW);

	// Set up the vertex array object.
	glGenVertexArrays(NumVAOs, VAOs);

	// VAO NUMBER ZERO.
	glBindVertexArray(VAOs[VAON0]);
	// Set up the vertex buffer objects.
	glGenBuffers(NumVBOs, VBOs);
	// VBO NUMBER ZERO.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n0VertPos) + sizeof(n0VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n0VertPos), n0VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n0VertPos), sizeof(n0VertCol), n0VertCol);
	// NUMBER ZERO vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n0VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER ONE.
	glBindVertexArray(VAOs[VAON1]);
	// VBO NUMBER ONE.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n1VertPos) + sizeof(n1VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n1VertPos), n1VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n1VertPos), sizeof(n1VertCol), n1VertCol);
	// NUMBER ONE vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n1VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER TWO.
	glBindVertexArray(VAOs[VAON2]);
	// VBO NUMBER TWO.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n2VertPos) + sizeof(n2VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n2VertPos), n2VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n2VertPos), sizeof(n2VertCol), n2VertCol);
	// NUMBER TWO vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n2VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER THREE.
	glBindVertexArray(VAOs[VAON3]);
	// VBO NUMBER THREE.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n3VertPos) + sizeof(n3VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n3VertPos), n3VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n3VertPos), sizeof(n3VertCol), n3VertCol);
	// NUMBER THREE vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n3VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER FOUR.
	glBindVertexArray(VAOs[VAON4]);
	// VBO NUMBER FOUR.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n4VertPos) + sizeof(n4VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n4VertPos), n4VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n4VertPos), sizeof(n4VertCol), n4VertCol);
	// NUMBER FOUR vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n4VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER FIVE.
	glBindVertexArray(VAOs[VAON5]);
	// VBO NUMBER FIVE.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n5VertPos) + sizeof(n5VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n5VertPos), n5VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n5VertPos), sizeof(n5VertCol), n5VertCol);
	// NUMBER FIVE vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n5VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER SIX.
	glBindVertexArray(VAOs[VAON6]);
	// VBO NUMBER SIX.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n6VertPos) + sizeof(n6VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n6VertPos), n6VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n6VertPos), sizeof(n6VertCol), n6VertCol);
	// NUMBER SIX vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n6VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER SEVEN.
	glBindVertexArray(VAOs[VAON7]);
	// VBO NUMBER SEVEN.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n7VertPos) + sizeof(n7VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n7VertPos), n7VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n7VertPos), sizeof(n7VertCol), n7VertCol);
	// NUMBER SEVEN vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n7VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER EIGHT.
	glBindVertexArray(VAOs[VAON8]);
	// VBO NUMBER EIGHT.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n8VertPos) + sizeof(n8VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n8VertPos), n8VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n8VertPos), sizeof(n8VertCol), n8VertCol);
	// NUMBER EIGHT vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n8VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// VAO NUMBER NINE.
	glBindVertexArray(VAOs[VAON9]);
	// VBO NUMBER NINE.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBON9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n9VertPos) + sizeof(n9VertCol), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(n9VertPos), n9VertPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(n9VertPos), sizeof(n9VertCol), n9VertCol);
	// NUMBER NINE vertex attributes.
	glVertexAttribPointer(VertPos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(VertCol, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(n9VertPos));
	glEnableVertexAttribArray(VertPos);
	glEnableVertexAttribArray(VertCol);

	// OpenGL setup.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
	glClearStencil(0x0);
	glEnable(GL_STENCIL_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

	glShadeModel(GL_FLAT);
	// Texturing.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Texture.
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Configure blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ...
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Build the Gui
void initGui()
{
	//Set idle function
	GLUI_Master.set_glutIdleFunc(idle);

	//Create GLUI window
	glui_window = GLUI_Master.create_glui("Blackjack", 0, 512, 512);

	//Create status_panel
	GLUI_Panel *status_panel = glui_window->add_panel("");

	//Create money_bet_panel
	GLUI_Panel *money_bet_panel = glui_window->add_panel_to_panel(status_panel, "Money Bet");

	//Add Bet Message text
	MONEY_BET = glui_window->add_statictext_to_panel(money_bet_panel, "$0");

	//Add column
	glui_window->add_column_to_panel(status_panel, false);

	//Create money_bet_panel
	GLUI_Panel *my_money_panel = glui_window->add_panel_to_panel(status_panel, "My Money");

	//Add My Monye text
	MY_MONEY = glui_window->add_statictext_to_panel(my_money_panel, "");

	//Create bet_command_panel
	GLUI_Panel *bet_command_panel = glui_window->add_panel("Bet System");

	//Add Decrease Button
	DECREASE = glui_window->add_button_to_panel(bet_command_panel, "Decrease", DECREASE_BUTTON, glui_callback);
	DECREASE->disable();

	//Add column
	glui_window->add_column_to_panel(bet_command_panel, false);

	//Add Increase Button
	INCREASE = glui_window->add_button_to_panel(bet_command_panel, "Increase", INCREASE_BUTTON, glui_callback);

	//Add Start match Button
	START_MATCH = glui_window->add_button_to_panel(bet_command_panel, "Start Match", START_MATCH_BUTTON, glui_callback);
	START_MATCH->disable();

	//Create dealer_panel
	GLUI_Panel *dealer_panel = glui_window->add_panel("");

	//Create dealer_cards_panel
	GLUI_Panel *dealer_cards_panel = glui_window->add_panel_to_panel(dealer_panel, "Dealer Cards");

	//Add Dealer_Cards label
	DEALER_CARDS = glui_window->add_statictext_to_panel(dealer_cards_panel, "");

	//Add column
	glui_window->add_column_to_panel(dealer_panel, false);

	//Create dealer_cards_panel
	GLUI_Panel *dealer_score_panel = glui_window->add_panel_to_panel(dealer_panel, "Dealer Score");

	//Add Dealer_Score label
	DEALER_SCORE = glui_window->add_statictext_to_panel(dealer_score_panel, "");

	//Create my_panel
	GLUI_Panel *my_panel = glui_window->add_panel("");

	//Create my_cards_panel
	GLUI_Panel *my_cards_panel = glui_window->add_panel_to_panel(my_panel, "My Cards");

	//Add My_Cards label
	MY_CARDS = glui_window->add_statictext_to_panel(my_cards_panel, "");

	//Add column
	glui_window->add_column_to_panel(my_panel, false);

	//Create my_score_panel
	GLUI_Panel *my_score_panel = glui_window->add_panel_to_panel(my_panel, "My Score");

	//Add Dealer_Score label
	MY_SCORE = glui_window->add_statictext_to_panel(my_score_panel, "");

	//Create my_panel
	GLUI_Panel *game_panel = glui_window->add_panel("Status");

	//Add Status label
	STATUS = glui_window->add_statictext_to_panel(game_panel, "");

	//Create card_command_panel
	GLUI_Panel *card_command_panel = glui_window->add_panel("Game Commands");

	//Add Stop Button
	STOP = glui_window->add_button_to_panel(card_command_panel, "Stop", STOP_BUTTON, glui_callback);
	STOP->disable();

	//Add column
	glui_window->add_column_to_panel(card_command_panel, false);

	//Add Continue Button
	CONTINUE = glui_window->add_button_to_panel(card_command_panel, "Next Match", CONTINUE_BUTTON, glui_callback);
	CONTINUE->disable();

	glui_window->set_main_gfx_window(main_window);
}

//Function that executes the commands
void glui_callback(int control_id)
{

	//Check the buttons pressed
	switch (control_id)
	{

	case DECREASE_BUTTON:
		if (bet > 0){
			bet -= 1;
			DECREASE->enable();
		}

		if (bet == 0){
			DECREASE->disable();
			START_MATCH->disable();
		}

		break;

	case INCREASE_BUTTON:

		if (bet < you->getMoney())
			bet += 1;

		if (bet > 0){
			DECREASE->enable();
			START_MATCH->enable();
		}

		break;
	case START_MATCH_BUTTON:
		yes = true;
		break;
	case CONTINUE_BUTTON:
		yes = true;
		break;
	case STOP_BUTTON:
		no = true;
		break;
	}

}

//Convert int to string
string convertInt(int number){

	string result;
	ostringstream convert;
	convert << number;
	result = convert.str();

	return result;
}

// Reshape callback function: whenever the window is reshaped, redefine the coordinate system and redraw the stencil area.
void reshape(int w, int h) {
	wndW = w;
	wndH = h;
	wndAR = float(wndW) / float(wndH);
	aspectRatio = float(h) / float(w);
	glutPostRedisplay();

}

// Keyboard callback function: standard keys.
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: { exit(EXIT_SUCCESS); break; }
	case 'y': case 'Y': case 13: {
		yes = true;
		break; }
	case 'n': case 'N': {
		no = true;
		break; }
	case 'w': case 'W': {
		bet += 1;
		break; }
	case 's': case 'S': {
		bet -= 1;
		break; }
	default: { break; }
	}

	glutPostRedisplay();
}

//Sum all elementos in the vector
int previousMrksSum = 0;
int currentMrksSum = 0;
int previousDealer = 0;
int count_dealer = 0;

//Game Logic
void gameLogic() {

	switch (current){

	case NEW_GAME:
		//Initialize deck
		deck = new Deck();

		//Create the players
		dealer = new Player(INITIAL_MONEY);
		you = new Player(INITIAL_MONEY);

		//Start new match
		current = NEW_MATCH;

		break;

	case NEW_MATCH:

		//Reset variables
		previousMrksSum = 0;
		currentMrksSum = 0;
		count_dealer = 0;
		bet = 0;

		//Reset labels
		STATUS->set_text("");
		DEALER_CARDS->set_text("");
		DEALER_SCORE->set_text("");
		MY_CARDS->set_text("");
		MY_SCORE->set_text("");

		INCREASE->enable();
		DECREASE->disable();

		CONTINUE->disable();
		STOP->disable();

		//Verify if the user has money to bet
		if (you->getMoney() <= 0) {
			current = END;

		}
		else{
			//Reset players
			dealer->reset();
			you->reset();

			MY_MONEY->set_text(("$" + convertInt(you->getMoney())).c_str());

			current = SET_BET;
		}

		break;

	case SET_BET:

		//Verify if the user wants to continue
		if (yes){

			//Reset
			yes = false;

			//Check if the bet is correct
			if (bet < 1 || bet > you->getMoney()){

				current = NEW_MATCH;

			}
			else{

				current = FIRST_CARDS;
			}
		}

		MONEY_BET->set_text(("$" + convertInt(bet)).c_str());

		break;

	case FIRST_CARDS:

		//Disable and Enable some buttons
		INCREASE->disable();
		DECREASE->disable();
		START_MATCH->disable();

		//Disable and Enable some buttons
		INCREASE->disable();
		DECREASE->disable();
		START_MATCH->disable();

		//Reset sum to the next turn
		currentMrksSum = 0;

		//Sum all the card in the array
		for (int index = 0; index < mrks.size(); index++){
			if (transfs[index].t().data[1] < 0)
				currentMrksSum += mrks[index] + 1;
		}

		//If the score changed, pick the last card
		if (currentMrksSum > previousMrksSum){

			previousDealer = currentMrksSum;

			//Add card to the message
			DEALER_CARDS->set_text(convertInt((int) currentMrksSum).c_str());

			//Verify if the dealer ...
			dealer->addScore(currentMrksSum);
			//Sum dealer score
			DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());
			current = YOUR_TURN;

		}

		break;
	case YOUR_TURN:

		int card;

		//Reset sum to the next turn
		currentMrksSum = 0;

		//Sum all the card in the array
		for (int index = 0; index < mrks.size(); index++){
			if (transfs[index].t().data[1] > 0)
				currentMrksSum += mrks[index] + 1;
			else{
				count_dealer++;
			}
		}

		//If the score changed, pick the last card
		if (currentMrksSum > previousMrksSum){
			card = currentMrksSum - previousMrksSum;

			//Update the previous sum
			previousMrksSum = currentMrksSum;

			//Set the text
			if (MY_CARDS->name == "")
				MY_CARDS->set_text((MY_CARDS->name + convertInt(card)).c_str());
			else
				MY_CARDS->set_text((MY_CARDS->name + ", " + convertInt(card)).c_str());

			//Adds score to user
			you->addScore(card);

			//Sum user score
			MY_SCORE->set_text(convertInt(you->getScore()).c_str());
		}

		//Add points to the player
		if (you->getScore() > 21) {
			current = LOST;
		}
		else if (count_dealer > 1){
			current = DEALER_TURN;

			//Reset sum to the next turn
			currentMrksSum = 0;
			previousMrksSum = previousDealer;
		}
		else {
			count_dealer = 0;
			current = YOUR_TURN;
		}

		break;

	case DEALER_TURN:

		//Reset sum to the next turn
		currentMrksSum = 0;

		//Sum all the card in the array
		for (int index = 0; index < mrks.size(); index++){
			if (transfs[index].t().data[1] < 0)
				currentMrksSum += mrks[index] + 1;
		}

		//If the score changed, pick the last card
		if (currentMrksSum > previousMrksSum){
			card = currentMrksSum - previousMrksSum;

			//Update the previous sum
			previousMrksSum = currentMrksSum;

			//Add card to the message
			DEALER_CARDS->set_text((DEALER_CARDS->name + ", " + convertInt(card)).c_str());

			//Verify if the dealer ...
			if (dealer->addScore(card)) {
				//Sum dealer score
				DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());
				current = WON;
			}
			else if (dealer->getScore() > you->getScore()) {
				current = LOST;
			}
			else if (dealer->getScore() == you->getScore() && you->getScore() >= 16) {
				current = EVEN;
			}

			//Sum dealer score
			DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());

		}

		break;
	case LOST:

		DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());

		STATUS->set_text("You Lost!!!");

		you->debit(bet);

		current = WAIT_NEW_MATCH;

		break;
	case WON:

		DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());

		STATUS->set_text("You Won!!!");

		you->credit(bet);

		current = WAIT_NEW_MATCH;

		break;
	case EVEN:

		DEALER_SCORE->set_text(convertInt(dealer->getScore()).c_str());

		STATUS->set_text("Even!!!");

		current = WAIT_NEW_MATCH;

		break;

	case WAIT_NEW_MATCH:

		//Enable commands buttons
		CONTINUE->enable();
		STOP->enable();

		//Verify if the user wants to continue
		if (yes){

			//Reset the control variables
			yes = false;

			current = NEW_MATCH;

		}
		else if (no){

			//Reset the control variables
			no = false;
			current = END;
		}

		break;
	case END:

		//Exit the application
		exit(EXIT_SUCCESS);
		break;
	}

	glutSetWindow(main_window);
	Sleep(40);
}

//Idle callback function.
void idle() {
	gameLogic();
	glutPostRedisplay();
}

// Display callback function.
void display() {

	updateOpenGLProjMatrix(frame.size().width, frame.size().height);
	// Grab a video frame and iterate until a video frame is available (and the window is alive).
	cap.grab();
	if (!(cap.retrieve(frame))) { glutLeaveMainLoop(); }
	//Get the data from cam
	mrkDetective->processFrame(frame);
	transfs = mrkDetective->getTransformations();
	mrks = mrkDetective->getIds();

	// Clearing buffers.
	glViewport(0, 0, (GLsizei)wndW, (GLsizei)wndH);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	// Draw the background with the current video frame.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// Configure the texture image data and size and format (inverting channels).
	if (frame.data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			frame.size().width, frame.size().height, 0,
			GL_BGR, GL_UNSIGNED_BYTE, frame.data);
	}
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (wndAR < 1.0f) { gluOrtho2D(-0.5, 0.5, -0.5f / wndAR, 0.5f / wndAR); }
	else { gluOrtho2D(-0.5 * wndAR, 0.5 * wndAR, -0.5, 0.5); }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	// Update the texture aspect ratio to properly resize the quad.
	texAR = (GLfloat)frame.size().width / (GLfloat)frame.size().height;

	float vx = 0.0f;
	float vy = 0.0f;

	if (wndAR < texAR) {
		vx = 0.5f * std::max(1.0f, wndAR);
		vy = (0.5f / texAR) * wndAR;
	}
	else {
		vx = 0.5f * texAR;
		vy = 0.5f;
	}

	// THIS SECTION IS RENDERED USING OLD OPENGL (NO SHADERS)!
	glUseProgram(0);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(-vx, -vy);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(vx, -vy);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(vx, vy);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-vx, vy);
	glEnd();
	glPopMatrix();

	float scalingFactor = std::min(float(wndW) / float(frame.size().width), float(wndH) / float(frame.size().height));
	float offsetX = wndW - (frame.size().width*scalingFactor);
	float offsetY = wndH - (frame.size().height*scalingFactor);
	glViewport(offsetX / 2.0f, offsetY / 2.0f, (GLsizei)(frame.size().width*scalingFactor), (GLsizei)(frame.size().height*scalingFactor));

	float th = float(GetTickCount() & 0x1FFF) / float(0x1FFF);
	static const vmath::vec3 X(1.0F, 0.0F, 0.0F);
	static const vmath::vec3 Y(0.0F, 1.0F, 0.0F);
	static const vmath::vec3 Z(0.0F, 0.0F, 1.0F);
	vmath::mat4 matrixProj;
	vmath::mat4 matrixModel;

	//For each marker detected
	for (size_t mId = 0; mId < transfs.size(); mId++) {

		//Get the marker position
		Transformation& t = transfs[mId];

		// THIS SECTION IS RENDERED USING MODERN OPENGL (VERTEX AND FRAGMENT SHADERS)!
		glUseProgram(shaderProg.id);

		// Clearing buffers: do not override last number!
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 0x1, 0x1);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

		// Set up the modelview and projection matrices
		matrixModel = vmath::translate(((GLfloat)t.t().data[0]) * 3.5F, ((GLfloat)t.t().data[1]) * 1.8F, ((GLfloat)t.t().data[2]) * 1.1F) * vmath::rotate(th * 360.0F, Y);
		matrixProj = vmath::frustum(-1.5F, 1.5F, -aspectRatio, aspectRatio, 1.0F, 500.0F);

		// Update the uniform variables in the vertex shader.
		glUniformMatrix4fv(locMatrixModel, 1, GL_FALSE, matrixModel);
		glUniformMatrix4fv(locMatrixProj, 1, GL_FALSE, matrixProj);

		// Clearing buffers
		glClear(GL_DEPTH_BUFFER_BIT);

		//Depending on the marker
		switch (mrks[mId] + 1) {
		case 1: {

			//Draw the number ONE
			glBindVertexArray(VAOs[VAON1]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON1]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 2: {

			//Draw the number TWO
			glBindVertexArray(VAOs[VAON2]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON2]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 3: {

			//Draw the number THREE
			glBindVertexArray(VAOs[VAON3]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON3]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 4: {

			//Draw the number FOUR
			glBindVertexArray(VAOs[VAON4]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON4]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 5: {

			//Draw the number FIVE
			glBindVertexArray(VAOs[VAON5]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON5]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 6: {

			//Draw the number SIX
			glBindVertexArray(VAOs[VAON6]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON6]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 7: {

			//Draw the number SEVEN
			glBindVertexArray(VAOs[VAON7]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON7]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 8: {

			//Draw the number EIGHT
			glBindVertexArray(VAOs[VAON8]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON8]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 9: {
			//Draw the number NINE
			glBindVertexArray(VAOs[VAON9]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON9]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		case 10: {

			//Draw the number TEN
			glBindVertexArray(VAOs[VAON0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBON0]);
			glDrawElements(GL_TRIANGLES, 190, GL_UNSIGNED_SHORT, NULL);

			break; }
		default: { break; }
		}

	}

	glPopMatrix();
	// Double buffering.
	glutSwapBuffers();
}