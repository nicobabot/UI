#include"UI_Slider.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "p2Log.h"
#include "UI.h"
#include "UI_Image_Buttons_Letters.h"
#include "UI_Letters_NonStatic_Static.h"
#include"Color.h"
UI_Slider::UI_Slider()
{
}

UI_Slider::UI_Slider(UI_Type type, SDL_Rect* rect, p2SString *text, iPoint pos, iPoint SliderLinePos, SDL_Rect * textrect, SDL_Rect * ViewPortRect, SDL_Rect * VerticalSliderBackgroundRect, SDL_Rect * VerticalSliderLineRect, bool movable) : UI(type, pos, rect, movable)
{
	this->text = *text;
	if (textrect != nullptr) {
		this->textrect.x = textrect->x;
		this->textrect.y = textrect->y;
		this->textrect.w = textrect->w;
		this->textrect.h = textrect->h;
	}
	if (ViewPortRect != nullptr) {
		this->ViewPortRect.x = pos.x-150;
		this->ViewPortRect.y = pos.y+100;
		this->ViewPortRect.w = ViewPortRect->w;
		this->ViewPortRect.h = ViewPortRect->h;
	}
	this->VerticalSliderLineRect.x = VerticalSliderLineRect->x;
	this->VerticalSliderLineRect.y = VerticalSliderLineRect->y;
	this->VerticalSliderLineRect.w = VerticalSliderLineRect->w;
	this->VerticalSliderLineRect.h = VerticalSliderLineRect->h;

	this->VerticalSliderBackgroundRect.x = VerticalSliderBackgroundRect->x;
	this->VerticalSliderBackgroundRect.y = VerticalSliderBackgroundRect->y;
	this->VerticalSliderBackgroundRect.w = VerticalSliderBackgroundRect->w;
	this->VerticalSliderBackgroundRect.h = VerticalSliderBackgroundRect->h;

	this->UI_Rect.x = rect->x;
	this->UI_Rect.y = rect->y;
	this->UI_Rect.w = rect->w;
	this->UI_Rect.h = rect->h;

	this->UI_Collision.x = pos.x;
	this->UI_Collision.y = pos.y;
	this->UI_Collision.w = rect->w;
	this->UI_Collision.h = rect->h;
	this->movable = movable;

	this->SliderLinePos = SliderLinePos;

	OriginalCamera.x = App->render->camera.x;
	OriginalCamera.y = App->render->camera.y;

	ModifText(*text);
}

UI_Slider::~UI_Slider()
{
}

void UI_Slider::Draw(UI * item)
{
	
	App->render->Blit(App->gui->GetAtlasNotConst(), ((UI_Slider*)item)->SliderLinePos.x - App->render->camera.x, ((UI_Slider*)item)->SliderLinePos.y - App->render->camera.y, &((UI_Slider*)item)->VerticalSliderBackgroundRect);
	App->render->Blit(App->gui->GetAtlasNotConst(), ((UI_Slider*)item)->SliderLinePos.x - App->render->camera.x, ((UI_Slider*)item)->SliderLinePos.y- App->render->camera.y, &((UI_Slider*)item)->VerticalSliderLineRect);
	App->render->Blit(App->gui->GetAtlasNotConst(), item->Getpos().x - App->render->camera.x, item->Getpos().y - App->render->camera.y, &((UI_Slider*)item)->GetRect());

	App->render->DrawQuad(((UI_Slider*)item)->ViewPortRect,246,246,246,255,false,false);
	
	SDL_RenderSetViewport(App->render->renderer, &((UI_Slider*)item)->ViewPortRect);
	for (int i = 0; i < texturestext.Count(); i++) {
		App->render->Blit(texturestext[i], 0 - App->render->camera.x, 0 - App->render->camera.y);
		//SDL_DestroyTexture(texturestext[i]);
	}
	SDL_RenderSetViewport(App->render->renderer, NULL);
}

void UI_Slider::ModifButtonSlider(UI* item, UI_Collision_Type state)
{

	iPoint itempoint;
	switch (state) {
	case left_click:
		click = true;
		break;
	case left_click_off:
		click = false;
		break;
	}

	if (click == true) {
		itempoint = item->Getpos();
		if (movable == true && itempoint.y <= ((UI_Slider*)item)->SliderLinePos.y +((UI_Slider*)item)->VerticalSliderLineRect.h - ((UI_Slider*)item)->UI_Rect.h && itempoint.y >= ((UI_Slider*)item)->SliderLinePos.y) {
			int motx, moty;
			App->input->GetMouseMotion(motx, moty);
			if (itempoint.y + moty >((UI_Slider*)item)->SliderLinePos.y +((UI_Slider*)item)->VerticalSliderLineRect.h - ((UI_Slider*)item)->UI_Rect.h && itempoint.y || itempoint.y + moty < ((UI_Slider*)item)->SliderLinePos.y) {
			}
			else {
				itempoint.y += moty;
			}
		}
		//calc value of slider
		float sliderbutton_y = itempoint.y;
		float sliderbutton_h = ((UI_Slider*)item)->UI_Rect.h;
		float minimumhsliderbarr = ((UI_Slider*)item)->SliderLinePos.y;
		float maximumsliderbarr = ((UI_Slider*)item)->VerticalSliderLineRect.h;
		result = 100 * ((sliderbutton_y - minimumhsliderbarr) / (maximumsliderbarr - sliderbutton_h));
		LOG("Result:%f", result);
		item->SetPosition(itempoint.x, itempoint.y);
		
		UI_Collision.x = itempoint.x;
		UI_Collision.y = itempoint.y;
	}	
}

void UI_Slider::ModifText(p2SString item)
{
	char* str = item.GetStringNotConst();
	char *next_token1 = NULL;
	char seps[] = ".,";
	token1.PushBack(strtok_s(str, seps, &next_token1));
	if (token1.Count() > 0) {
		while (*next_token1 !='\0')
		{
			token1.PushBack(strtok_s(NULL, seps, &next_token1));
		}
	}
	for (int i = 0; i < token1.Count(); i++) {
		texturestext.PushBack(App->font->Print(token1[i]));
	}
}

