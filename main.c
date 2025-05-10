#include "scene.h"

int main() {

	VisualNovel visualNovel = {0};

	addDialogue(&visualNovel, 0, "", "The clanking of gears, the rhythmic hiss of steam vents, and the low hum of turbines echoed through my underground factory — a steel womb I had crafted with my own hands.");
	addDialogue(&visualNovel, 0, "", "Pipes crisscrossed above me like vines in a jungle, spewing wisps of vapor that danced in the amber glow of gaslight.");
	addDialogue(&visualNovel, 0, "", "My boots clanked against the catwalk as I adjusted a brass dial on one of the pressure chambers.");
	addDialogue(&visualNovel, 0, "", "I am Phoebe the Ferret.");
	addDialogue(&visualNovel, 0, "", "Inventor.");
	addDialogue(&visualNovel, 0, "", "Tinkerer.");
	addDialogue(&visualNovel, 0, "", "Gunsmith.");
	addDialogue(&visualNovel, 0, "", "Not the kind that hides in shadows or lurks in alleys — no, I build my world, bolt by bolt, in this cathedral of steam and fire.");
	addDialogue(&visualNovel, 0, "", "My latest project, a new variant of my burst rifle, hummed quietly on the bench — almost ready.");
	addDialogue(&visualNovel, 0, "", "That was when I heard it.");
	addDialogue(&visualNovel, 0, "", "The familiar sound of steel toes on iron steps, heavier than mine.");
	addDialogue(&visualNovel, 0, "", "Confident.");
	addDialogue(&visualNovel, 0, "", "Purposeful.");
	addDialogue(&visualNovel, 0, "", "Mercer.");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“Hope I’m not interrupting your court of cogs, sweetheart,”");
	addDialogue(&visualNovel, 0, "", "came his voice, a little raspy, a little smug.");
	addDialogue(&visualNovel, 0, "", "I turned, wiping grease from my cheek with the back of my glove.");
	addDialogue(&visualNovel, 0, "", "There he stood — Mercer the Hyena, hunter of the wastes, rifle slung across his shoulder, smirk as sharp as ever.");
	addDialogue(&visualNovel, 0, "Phoebe the Ferret", "“Well,”");
	addDialogue(&visualNovel, 0, "", "I said, raising an eyebrow,");
	addDialogue(&visualNovel, 0, "Phoebe the Ferret", "“either you missed me, or something broke and you're too proud to admit it.”");
	addDialogue(&visualNovel, 0, "", "He chuckled.");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“Can’t it be both?”");
	addDialogue(&visualNovel, 0, "", "I stepped down from the platform, approaching him with a wry grin.");
	addDialogue(&visualNovel, 0, "Phoebe the Ferret", "“What is it this time? Scope jammed? Trigger snapped? Or did your pride finally overheat?”");
	addDialogue(&visualNovel, 0, "", "He reached into his coat and pulled out a brass cylinder, dented and cracked down the middle.");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“Your last tuning crystal cracked mid-shot. Lucky it didn’t blow my face off.”");
	addDialogue(&visualNovel, 0, "", "I took the part and inspected it, frowning.");
	addDialogue(&visualNovel, 0, "Phoebe the Ferret", "“This wasn’t calibrated for that kind of charge... were you trying to snipe a dragon again?”");
	addDialogue(&visualNovel, 0, "", "He shrugged.");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“Only a siege cannon. Close enough.”");
	addDialogue(&visualNovel, 0, "", "I shook my head, muttering,");
	addDialogue(&visualNovel, 0, "Phoebe the Ferret", "“You’re going to get yourself killed one day.”");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“I figured that’s why I keep coming back to you,”");
	addDialogue(&visualNovel, 0, "", "he said, softer now.");
	addDialogue(&visualNovel, 0, "Mercer the Hyena", "“You always keep me in one piece.”");
	addDialogue(&visualNovel, 0, "", "There was something in his eyes.");
	addDialogue(&visualNovel, 0, "", "That glint.");
	addDialogue(&visualNovel, 0, "", "Not just from the reflection of the boiler flames.");
	addDialogue(&visualNovel, 0, "", "Something a little warmer.");
	addDialogue(&visualNovel, 0, "", "I could answer with a tease, dig into the work, or maybe... just maybe, ask him why he really came.");
	addDialogue(&visualNovel, 0, "", "What should I do?");
	addChoice(&visualNovel, 0, "“Let’s fix this first before it blows your head off next time.” (Focus on the work — professional and practical.)", 1);
	addChoice(&visualNovel, 0, "“You didn’t really come all this way just to fix a cracked crystal, did you?” (Ask him directly — get personal.)", 2);
	addChoice(&visualNovel, 0, "“Admit it, Mercer. You just missed me.” (Teasing — flirtatious tone.)", 3);

	addDialogue(&visualNovel, 1, "", "I took the cracked crystal in both hands, already scanning its fractures and burns.");
	addDialogue(&visualNovel, 1, "Phoebe the Ferret", "“Let’s fix this first before it blows your head off next time.”");
	addDialogue(&visualNovel, 1, "Mercer the Hyena", "“I knew you'd say that.”");
	addDialogue(&visualNovel, 1, "", "I walked over to my tuning bench and gently placed the cylinder into a brass clamp.");
	addDialogue(&visualNovel, 1, "Phoebe the Ferret", "“Sit tight. This one’s going to need a bit of finesse.”");
	addDialogue(&visualNovel, 1, "", "The whir of my lens goggles snapped down over my eyes as I ignited the flame torch.");
	addDialogue(&visualNovel, 1, "", "Sparks danced like fireflies while Mercer leaned casually against the nearest support beam.");
	addDialogue(&visualNovel, 1, "Mercer the Hyena", "“Y'know, you're the only person who talks to machines like they’re family.”");
	addDialogue(&visualNovel, 1, "Phoebe the Ferret", "“That’s because they don’t lie, don’t disappoint, and they do exactly what I design them to do.”");
	addDialogue(&visualNovel, 1, "", "He fell silent after that, watching me with that same unreadable glint in his eyes.");
	addChoice(&visualNovel, 1, "“So... really, what happened out there?” (Ask for details about his mission)", 4);
	addChoice(&visualNovel, 1, "“You keep staring. Something on your mind?” (Probe his mood)", 5);
	addChoice(&visualNovel, 1, "Keep working in silence. Let him talk if he wants to. (Remain focused)", 6);

	addDialogue(&visualNovel, 2, "", "I narrowed my eyes, holding the cracked crystal up between us.");
	addDialogue(&visualNovel, 2, "Phoebe the Ferret", "You didn’t really come all this way just to fix a cracked crystal, did you?");
	addDialogue(&visualNovel, 2, "", "He didn’t answer right away — just shifted his weight and looked past me, toward the humming heart of my workshop.");
	addDialogue(&visualNovel, 2, "Mercer the Hyena", "Guess I needed to see something real for a change.");
	addDialogue(&visualNovel, 2, "", "His voice dropped the playful edge. It wasn’t often he spoke like that.");
	addDialogue(&visualNovel, 2, "Phoebe the Ferret", "Things getting rough out there?");
	addDialogue(&visualNovel, 2, "Mercer the Hyena", "They always are. Doesn’t bother me much. But lately... I dunno. Feels like the world’s creaking under its own weight.");
	addDialogue(&visualNovel, 2, "", "I looked at him a moment longer, then gently placed the cracked part on the bench behind me.");
	addDialogue(&visualNovel, 2, "Phoebe the Ferret", "You’re not just here for repairs.");
	addDialogue(&visualNovel, 2, "Mercer the Hyena", "...No. I’m not.");
	addDialogue(&visualNovel, 2, "", "There was silence for a moment, thick with steam and meaning. The warmth in the factory wasn’t just from the boilers now.");
	addChoice(&visualNovel, 2, "“You can stay for a while. I’ll make tea.” (Let him rest — show quiet support.)", 7);
	addChoice(&visualNovel, 2, "“What is it you’re really looking for, Mercer?” (Dig deeper — serious and direct.)", 8);
	addChoice(&visualNovel, 2, "“Getting sentimental on me, are you?” (Deflect with charm — keep it light.)", 9);

	addDialogue(&visualNovel, 3, "", "I tilted my head, a sly smirk tugging at my lips as I leaned in just slightly.");
	addDialogue(&visualNovel, 3, "Phoebe the Ferret", "Admit it, Mercer. You just missed me.");
	addDialogue(&visualNovel, 3, "", "He blinked, caught off guard for just a second before the corner of his mouth curled upward.");
	addDialogue(&visualNovel, 3, "Mercer the Hyena", "Tch. What gave me away — the three-day trek through the canyons or the part where I didn’t bother knocking?");
	addDialogue(&visualNovel, 3, "", "I chuckled, the sound mixing with the hiss of steam around us.");
	addDialogue(&visualNovel, 3, "Phoebe the Ferret", "I’d say both. But mostly the not-knocking part.");
	addDialogue(&visualNovel, 3, "", "He took a slow step closer, eyes scanning my face, like he was searching for something underneath the soot and goggles.");
	addDialogue(&visualNovel, 3, "Mercer the Hyena", "You know, I never really liked quiet places.");
	addDialogue(&visualNovel, 3, "", "I raised a brow.");
	addDialogue(&visualNovel, 3, "Phoebe the Ferret", "Because they make you think?");
	addDialogue(&visualNovel, 3, "", "He laughed, low and genuine.");
	addDialogue(&visualNovel, 3, "Mercer the Hyena", "Exactly. And somehow, yours is the only kind of noise that keeps me sane.");
	addChoice(&visualNovel, 3, "“Keep talking like that and I might start thinking you actually care.”", 10);
	addChoice(&visualNovel, 3, "“Careful, Mercer. You’re starting to sound romantic.”", 11);
	addChoice(&visualNovel, 3, "“You want to tinker with weapons or feelings today?”", 12);

	addDialogue(&visualNovel, 4, "Phoebe the Ferret", "“So... really, what happened out there?”");
	addDialogue(&visualNovel, 4, "Mercer the Hyena", "“A convoy ambush. We were escorting a supply train from the Eastern Ridge.”");
	addDialogue(&visualNovel, 4, "Phoebe the Ferret", "“Bandits?”");
	addDialogue(&visualNovel, 4, "Mercer the Hyena", "“No. Something... else. They moved like shadows. Didn’t speak. Didn’t bleed.”");
	addDialogue(&visualNovel, 4, "", "His voice was lower now, like even saying it out loud made it real.");
	addDialogue(&visualNovel, 4, "Phoebe the Ferret", "“You’re saying they weren’t human?”");
	addDialogue(&visualNovel, 4, "Mercer the Hyena", "“Maybe Animorphs gone rogue. Maybe not Anima at all.”");
	addDialogue(&visualNovel, 4, "", "The torch in my hand sputtered as I turned the flame down, focusing on his words.");
	addDialogue(&visualNovel, 4, "Phoebe the Ferret", "“Sounds like something I should prepare for.”");
	addDialogue(&visualNovel, 4, "Mercer the Hyena", "“That’s why I came. You’re the only one who can build what I need.”");
	addChoice(&visualNovel, 4, "“Then tell me exactly what you’re facing. I’ll build for it.” (Get serious)", 13);
	addChoice(&visualNovel, 4, "“You’re scared.” (Call him out gently)", 14);
	addChoice(&visualNovel, 4, "“Heh. Sounds like you need me more than you admit.” (Playfully smug)", 15);

	addDialogue(&visualNovel, 5, "Phoebe the Ferret", "“You keep staring. Something on your mind?”");
	addDialogue(&visualNovel, 5, "Mercer the Hyena", "“Yeah... just thinking how this place feels like a different world.”");
	addDialogue(&visualNovel, 5, "", "He wasn’t smiling now. Just watching the glow of the forge reflect in the brass casings.");
	addDialogue(&visualNovel, 5, "Phoebe the Ferret", "“It is. Down here, time slows. Nothing but gears and ideas.”");
	addDialogue(&visualNovel, 5, "Mercer the Hyena", "“You built it all yourself?”");
	addDialogue(&visualNovel, 5, "Phoebe the Ferret", "“Every pipe, every switch. No one helped me. Didn’t need anyone.”");
	addDialogue(&visualNovel, 5, "", "A pause. He seemed to be measuring his next words carefully.");
	addDialogue(&visualNovel, 5, "Mercer the Hyena", "“Ever wonder what it’d be like... if you let someone in?”");
	addDialogue(&visualNovel, 5, "", "That caught me off guard. My hands froze over the clamp.");
	addDialogue(&visualNovel, 5, "Phoebe the Ferret", "“I don’t let people in, Mercer. They tend to break things I can’t fix.”");
	addChoice(&visualNovel, 5, "“You wouldn’t break anything... would you?” (Cautiously vulnerable)", 16);
	addChoice(&visualNovel, 5, "“That sounded dangerously close to flirting.” (Deflect with humor)", 17);
	addChoice(&visualNovel, 5, "“I think we should both stay focused.” (Back to business)", 18);

	addDialogue(&visualNovel, 6, "", "I focused on the repair, letting the silence settle.");
	addDialogue(&visualNovel, 6, "", "The soft whirr of my tools and the occasional hiss of venting steam filled the space between us.");
	addDialogue(&visualNovel, 6, "", "For a few minutes, he said nothing. Just watched me work.");
	addDialogue(&visualNovel, 6, "Mercer the Hyena", "“You ever get tired of being down here alone?”");
	addDialogue(&visualNovel, 6, "Phoebe the Ferret", "“Alone isn’t the same as lonely.”");
	addDialogue(&visualNovel, 6, "Mercer the Hyena", "“Still. Feels like a fortress. Cold walls. Locked doors.”");
	addDialogue(&visualNovel, 6, "Phoebe the Ferret", "“I like my walls. They protect what matters.”");
	addDialogue(&visualNovel, 6, "Mercer the Hyena", "“What’s behind them?”");
	addDialogue(&visualNovel, 6, "", "I didn’t answer right away. The truth was... I wasn’t sure.");
	addDialogue(&visualNovel, 6, "Phoebe the Ferret", "“Maybe something worth protecting. Maybe nothing at all.”");
	addChoice(&visualNovel, 6, "“Why are you really here, Mercer?” (Challenge him)", 19);
	addChoice(&visualNovel, 6, "“You want to stay a while?” (Invite him to linger)", 20);
	addChoice(&visualNovel, 6, "“I’d rather talk about upgrades.” (Keep things strictly mechanical)", 21);

	addDialogue(&visualNovel, 7, "Phoebe the Ferret", "You can stay for a while. I’ll make tea.");
	addDialogue(&visualNovel, 7, "", "He blinked, almost surprised, then gave a small nod.");
	addDialogue(&visualNovel, 7, "Mercer the Hyena", "That... sounds good. Yeah.");
	addDialogue(&visualNovel, 7, "", "I turned to the copper kettle nestled in the steam alcove, flipping the lever to heat it.");
	addDialogue(&visualNovel, 7, "Phoebe the Ferret", "Still take yours with clove and rustleaf?");
	addDialogue(&visualNovel, 7, "Mercer the Hyena", "You remember.");
	addDialogue(&visualNovel, 7, "", "I handed him a warm mug, and he took it with both hands like it was something fragile.");
	addDialogue(&visualNovel, 7, "Mercer the Hyena", "Place hasn’t changed. Still smells like oil and cinnamon.");
	addDialogue(&visualNovel, 7, "Phoebe the Ferret", "Some things are better left unchanged.");
	addDialogue(&visualNovel, 7, "", "We stood there, quietly sipping — the weight of the world, if only for a moment, shut out by hissing pipes and clinking cups.");
	addChoice(&visualNovel, 7, "“You could stay longer… if you wanted.” (Offer comfort — hint at something deeper.)", 22);
	addChoice(&visualNovel, 7, "“Do you ever think about stopping?” (Question his wandering ways.)", 23);
	addChoice(&visualNovel, 7, "“That crack in the tuning crystal… what really happened?” (Circle back to the job.)", 24);

	addDialogue(&visualNovel, 8, "Phoebe the Ferret", "What is it you’re really looking for, Mercer?");
	addDialogue(&visualNovel, 8, "", "He sighed, his smirk fading completely.");
	addDialogue(&visualNovel, 8, "Mercer the Hyena", "I don’t know anymore.");
	addDialogue(&visualNovel, 8, "", "He moved to the railing, staring down at the pulsing engine core below.");
	addDialogue(&visualNovel, 8, "Mercer the Hyena", "At first it was just about surviving. Then hunting. Then... glory, maybe?");
	addDialogue(&visualNovel, 8, "Phoebe the Ferret", "But it’s not enough now.");
	addDialogue(&visualNovel, 8, "Mercer the Hyena", "Exactly.");
	addDialogue(&visualNovel, 8, "", "He looked over his shoulder at me. His eyes weren’t sharp — they were tired.");
	addDialogue(&visualNovel, 8, "Mercer the Hyena", "Sometimes I think the only thing that makes sense anymore is you. This place. The work.");
	addDialogue(&visualNovel, 8, "", "I wasn’t expecting that — but I didn’t look away.");
	addChoice(&visualNovel, 8, "“Then stay. Help me finish what I’ve started.” (Invite him to stay — partnership.)", 25);
	addChoice(&visualNovel, 8, "“You’re not broken, Mercer. Just... lost.” (Comfort him — reassure.)", 26);
	addChoice(&visualNovel, 8, "“So what are you going to do about it?” (Challenge him — provoke action.)", 27);

	addDialogue(&visualNovel, 9, "Phoebe the Ferret", "Getting sentimental on me, are you?");
	addDialogue(&visualNovel, 9, "", "He let out a breath that was half laugh, half groan.");
	addDialogue(&visualNovel, 9, "Mercer the Hyena", "Stars, don’t make me regret opening up.");
	addDialogue(&visualNovel, 9, "", "I leaned back against the workbench, arms crossed, grinning.");
	addDialogue(&visualNovel, 9, "Phoebe the Ferret", "Too late. It’s in the logbook now.");
	addDialogue(&visualNovel, 9, "Mercer the Hyena", "Fine, fine. I’ll pretend it was the boiler fumes messing with my head.");
	addDialogue(&visualNovel, 9, "Phoebe the Ferret", "Or maybe you’re just warming up after all these years.");
	addDialogue(&visualNovel, 9, "", "He gave me a look — half playful, half genuine.");
	addDialogue(&visualNovel, 9, "Mercer the Hyena", "Careful, Phoebe. You keep talking like that, I might never leave.");
	addDialogue(&visualNovel, 9, "", "The words hung in the air, daring me to press further or let them drift away like steam in the vents.");
	addChoice(&visualNovel, 9, "“Then don’t.” (Flirt — invite him closer.)", 28);
	addChoice(&visualNovel, 9, "“You always were bad at goodbyes.” (Nostalgic — friendly tease.)", 29);
	addChoice(&visualNovel, 9, "“Right. Let’s see if your aim’s still any good.” (Change subject — go to the workshop.)", 30);

	addDialogue(&visualNovel, 10, "", "I gave him a mock glare, crossing my arms but unable to hide my grin.");
	addDialogue(&visualNovel, 10, "Phoebe the Ferret", "Keep talking like that and I might start thinking you actually care.");
	addDialogue(&visualNovel, 10, "", "Mercer scratched the back of his head, suddenly more sheepish than smug.");
	addDialogue(&visualNovel, 10, "Mercer the Hyena", "Would it be so bad if I did?");
	addDialogue(&visualNovel, 10, "", "My heart skipped, but I masked it with a shrug.");
	addDialogue(&visualNovel, 10, "Phoebe the Ferret", "Depends. Do you care about me, or just the one who fixes your toys?");
	addDialogue(&visualNovel, 10, "", "He looked away briefly, jaw tightening.");
	addDialogue(&visualNovel, 10, "Mercer the Hyena", "You know I don’t let anyone else touch my rifle, right?");
	addDialogue(&visualNovel, 10, "", "There was something vulnerable under that tough veneer — something raw.");
	addDialogue(&visualNovel, 10, "Phoebe the Ferret", "...I know. I just like making you say it.");
	addChoice(&visualNovel, 10, "“Okay, now hand over the rest of the busted parts.” (Shift back to work.)", 31);
	addChoice(&visualNovel, 10, "“Is this the part where you kiss me or chicken out?”", 32);
	addChoice(&visualNovel, 10, "“Let’s go somewhere less... clangy.”", 33);

	addDialogue(&visualNovel, 11, "", "I narrowed my eyes playfully, stepping around him to grab a wrench from the table.");
	addDialogue(&visualNovel, 11, "Phoebe the Ferret", "Careful, Mercer. You’re starting to sound romantic.");
	addDialogue(&visualNovel, 11, "", "He leaned back against a support beam, arms folded, smirking.");
	addDialogue(&visualNovel, 11, "Mercer the Hyena", "Maybe I am. Doesn’t mean I’ll start writing poetry.");
	addDialogue(&visualNovel, 11, "", "I smirked, pretending to examine the broken crystal.");
	addDialogue(&visualNovel, 11, "Phoebe the Ferret", "Pity. I’d pay to hear a haiku about me and a grenade launcher.");
	addDialogue(&visualNovel, 11, "", "He laughed again, eyes bright. There was something electric in the air.");
	addDialogue(&visualNovel, 11, "Mercer the Hyena", "I’m not a poet, but I know what I like.");
	addDialogue(&visualNovel, 11, "", "I glanced up, meeting his gaze. It lingered.");
	addDialogue(&visualNovel, 11, "Phoebe the Ferret", "...And what do you like, exactly?");
	addChoice(&visualNovel, 11, "“Don’t answer that. I need to focus.” (Deflect with humor.)", 34);
	addChoice(&visualNovel, 11, "“If you’re serious, prove it.”", 35);
	addChoice(&visualNovel, 11, "“You’re not smooth, Mercer. But you’re trying.”", 36);

	addDialogue(&visualNovel, 12, "", "I placed the cracked part back on the table, dusting my gloves off.");
	addDialogue(&visualNovel, 12, "Phoebe the Ferret", "So, you want to tinker with weapons or feelings today?");
	addDialogue(&visualNovel, 12, "", "He raised a brow, caught between a laugh and a groan.");
	addDialogue(&visualNovel, 12, "Mercer the Hyena", "Are those not the same thing with you?");
	addDialogue(&visualNovel, 12, "", "I laughed, walking over to my forge and igniting the pilot flame.");
	addDialogue(&visualNovel, 12, "Phoebe the Ferret", "Depends on the calibration. Feelings have worse recoil.");
	addDialogue(&visualNovel, 12, "", "Mercer followed, standing beside me at the anvil.");
	addDialogue(&visualNovel, 12, "Mercer the Hyena", "I came here for repairs... and maybe a little more.");
	addDialogue(&visualNovel, 12, "", "I glanced sideways at him, hammer in hand.");
	addDialogue(&visualNovel, 12, "Phoebe the Ferret", "You better be more specific before I start forging conclusions.");
	addChoice(&visualNovel, 12, "“Let’s talk seriously — are we something?”", 37);
	addChoice(&visualNovel, 12, "“More what? Tea? Trouble?”", 38);
	addChoice(&visualNovel, 12, "“Hand me that spanner. Let’s pretend this is normal.”", 39);

	Scene scene = visualNovel.scenes[0];
	while (1) {
		printDialogue(scene.dialogues);
		if (endOfScene(scene)) {
			break;
		}
		scene = showChoices(scene);
	}

	freeVisualNovel(&visualNovel);

	return 0;
}
