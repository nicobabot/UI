#ifndef __UI_SLIDER_H__
#define __UI_SLIDER_H__

#include "p2SString.h"
#include"UI.h"
#include"p2PQueue.h"
#include"p2DynArray.h"

class UI_Letters_Static;


//-----------------------------------------------UI_Image-----------------------------------------------
class UI_Slider : public UI
{
public:

	UI_Slider();
	UI_Slider(UI_Type type, SDL_Rect* rect, p2SString *text ,iPoint pos, Slider_type slider_type, iPoint SliderLinePos, SDL_Rect * ViewPortRect = nullptr, SDL_Rect * VerticalSliderBackgroundRect = nullptr, SDL_Rect * VerticalSliderLineRect = nullptr,  bool movable = false, UI_Image *window_point=nullptr);
	~UI_Slider();
	void Draw(UI* item);
	void ModifButtonSlider(UI* item, UI_Collision_Type state);
	void ModifText(p2SString item);
	void SetCollision(iPoint * col);
private:
	Slider_type slider_type;
	p2SString text;
	SDL_Rect ViewPortRect;
	SDL_Rect VerticalSliderLineRect;
	iPoint SliderLinePos;
	SDL_Rect VerticalSliderBackgroundRect;
	//And the button rect/collider that inherit from UI
	iPoint OriginalCamera;
	bool click = false;
	float result;
	p2DynArray<char*> token1;
	p2DynArray<SDL_Texture*> texturestext;
	int Text_Tot_H=0;
	float incre;
	float original_y;
	bool move;
};

#endif