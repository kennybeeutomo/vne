#include "choice.h"
#include "dialogue.h"
#include "scene.h"

int main() {

	VisualNovel visualNovel = {0};
	Dialogue* dialogue;
	Choice* choice;

	dialogue = addDialogue(&visualNovel, 0, "", "Q1 of 4\n2+2=?");
	choice = addChoice(&visualNovel, 0, "2", 1); setFlag(choice, "badmath");
	choice = addChoice(&visualNovel, 0, "4", 2);
	choice = addChoice(&visualNovel, 0, "5", 1); setFlag(choice, "badmath");
	choice = addChoice(&visualNovel, 0, "8", 1); setFlag(choice, "badmath");

	dialogue = addDialogue(&visualNovel, 1, "", "That response is incorrect. Press any key to try again.");
	dialogue = addDialogue(&visualNovel, 1, "", "Q1 of 4\n3+2=?");
	choice = addChoice(&visualNovel, 1, "2", 1);
	choice = addChoice(&visualNovel, 1, "4", 1);
	choice = addChoice(&visualNovel, 1, "5", 2);
	choice = addChoice(&visualNovel, 1, "8", 1);

	dialogue = addDialogue(&visualNovel, 2, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 2, "", "Q2 of 4\nWhat is your subjective reaction to this image?\n\n^_^\n\nANSWER:");
	choice = addChoice(&visualNovel, 2, "Content", 3);
	choice = addChoice(&visualNovel, 2, "Mountain", 3); setFlag(choice, "objective");
	choice = addChoice(&visualNovel, 2, "Face", 3); setFlag(choice, "objective");
	choice = addChoice(&visualNovel, 2, "Angry", 3);

	dialogue = addDialogue(&visualNovel, 3, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 3, "", "Q3 of 4\nWhat best describes a person?\n\nANSWER:");
	choice = addChoice(&visualNovel, 3, "A human being", 4); setFlag(choice, "humanbeing");
	choice = addChoice(&visualNovel, 3, "A citizen", 4); setFlag(choice, "citizen");
	choice = addChoice(&visualNovel, 3, "A being of negative entropy", 4); setFlag(choice, "negativeentropy");
	choice = addChoice(&visualNovel, 3, "A rational animal", 4); setFlag(choice, "rationalanimal");
	choice = addChoice(&visualNovel, 3, "A problem solving system", 4); setFlag(choice, "problemsolving");

	dialogue = addDialogue(&visualNovel, 4, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 4, "", "Q4 of 4\nYou're walking through the desert and come across a thirsty traveller. His eyes bulge from slow dehydration. You have water, but you're not sure how far it is to the next oasis. What do you do?\n\nANSWER: ");
	choice = addChoice(&visualNovel, 4, "Offer half the water", 5);
	choice = addChoice(&visualNovel, 4, "Offer all the water", 5);
	choice = addChoice(&visualNovel, 4, "Ignore him", 5);
	choice = addChoice(&visualNovel, 4, "Ask what you're doing in the desert", 5);
	choice = addChoice(&visualNovel, 4, "Kill him and collect his blood in a flask for later", 5); setFlag(choice, "sociopath");

	dialogue = addDialogue(&visualNovel, 5, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 5, "", "Part 1 of the certification process is now complete.");
	dialogue = addDialogue(&visualNovel, 5, "", "Part 2 is designed to test the consistency of some of your outlier responses in the previous round. You will be presented with a series of statements. Please indicate your agreement where appropriate.");

	dialogue = addDialogue(&visualNovel, 5, "", "Q1 of 6\nSince all human beings are persons, and some human beings have psychological capacities similar to animals, some animals are therefore persons.\n\nANSWER: "); requireDialogueFlag(dialogue, "humanbeing");
	choice = addChoice(&visualNovel, 5, "Broadly agree", 6); requireChoiceFlag(choice, "humanbeing"); setFlag(choice, "animalsarepersons");
	choice = addChoice(&visualNovel, 5, "Broadly disagree", 6); requireChoiceFlag(choice, "humanbeing"); setFlag(choice, "persondenial");

	dialogue = addDialogue(&visualNovel, 5, "", "Q1 of 6\nSince only citizens can be persons, a hermit cannot be a person.\n\nANSWER:"); requireDialogueFlag(dialogue, "citizen");
	choice = addChoice(&visualNovel, 5, "Broadly agree", 6); requireChoiceFlag(choice, "citizen");
	choice = addChoice(&visualNovel, 5, "Broadly disagree", 6); requireChoiceFlag(choice, "citizen"); setFlag(choice, "persondenial");

	dialogue = addDialogue(&visualNovel, 5, "", "Q1 of 6\nSince negative entropy indicates personhood, microscopic organisms are also persons.\n\nANSWER:"); requireDialogueFlag(dialogue, "negativeentropy");
	choice = addChoice(&visualNovel, 5, "Broadly agree", 6); requireChoiceFlag(choice, "negativeentropy");
	choice = addChoice(&visualNovel, 5, "Broadly disagree", 6); requireChoiceFlag(choice, "negativeentropy"); setFlag(choice, "persondenial");

	dialogue = addDialogue(&visualNovel, 5, "", "Q1 of 6\nSince only animals can be persons, a machine could never be a person.\n\nANSWER:"); requireDialogueFlag(dialogue, "rationalanimal");
	choice = addChoice(&visualNovel, 5, "Broadly agree", 6); requireChoiceFlag(choice, "rationalanimal");
	choice = addChoice(&visualNovel, 5, "Broadly disagree", 6); requireChoiceFlag(choice, "rationalanimal"); setFlag(choice, "persondenial");

	dialogue = addDialogue(&visualNovel, 5, "", "Q1 of 6\nSince a person is merely a problem solving system, we could in principle build a person out of bits of string and tin cans.\n\nANSWER:"); requireDialogueFlag(dialogue, "problemsolving");
	choice = addChoice(&visualNovel, 5, "Broadly agree", 6); requireChoiceFlag(choice, "problemsolving");
	choice = addChoice(&visualNovel, 5, "Broadly disagree", 6); requireChoiceFlag(choice, "problemsolving"); setFlag(choice, "persondenial");

	dialogue = addDialogue(&visualNovel, 6, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 6, "", "Q2 of 6\nA person is under no authority other than that to which they consent.\n\nANSWER:");
	choice = addChoice(&visualNovel, 6, "Broadly agree", 7); setFlag(choice, "nomorals");
	choice = addChoice(&visualNovel, 6, "Broadly disagree", 7);

	dialogue = addDialogue(&visualNovel, 7, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 7, "", "Q3 of 6\nThe quality of life of persons ought be maximised.\n\nANSWER:");
	choice = addChoice(&visualNovel, 7, "Broadly agree", 8); setFlag(choice, "utilitarian");
	choice = addChoice(&visualNovel, 7, "Broadly disagree", 8);

	dialogue = addDialogue(&visualNovel, 8, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 8, "", "Q4 of 6\nValue is discovered.\n\nANSWER:");
	choice = addChoice(&visualNovel, 8, "Broadly agree", 9); setFlag(choice, "valuediscovered");
	choice = addChoice(&visualNovel, 8, "Broadly disagree", 9);

	dialogue = addDialogue(&visualNovel, 9, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 9, "", "Q5 of 6\nThe liberty of persons ought be maximised.\n\nANSWER:");
	choice = addChoice(&visualNovel, 9, "Broadly agree", 10); setFlag(choice, "liberal");
	choice = addChoice(&visualNovel, 9, "Broadly disagree", 10);

	dialogue = addDialogue(&visualNovel, 10, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 10, "", "Q6 of 6\nValue is created.\n\nANSWER:");
	choice = addChoice(&visualNovel, 10, "Broadly agree", 11); setFlag(choice, "valuecreated");
	choice = addChoice(&visualNovel, 10, "Broadly disagree", 11);

	dialogue = addDialogue(&visualNovel, 11, "", "Your input has been accepted.");
	dialogue = addDialogue(&visualNovel, 11, "", "Thank you. The certification process is now complete. You will receive a notification when your user profile has been generated.");

	startVisualNovel(&visualNovel);
	freeVisualNovel(&visualNovel);

	return 0;
}
