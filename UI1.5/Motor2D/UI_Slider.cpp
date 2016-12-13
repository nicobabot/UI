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

UI_Slider::UI_Slider(UI_Type type, SDL_Rect* rect, p2SString *text, iPoint pos, Slider_type slider_type, iPoint SliderLinePos, SDL_Rect * ViewPortRect, SDL_Rect * VerticalSliderBackgroundRect, SDL_Rect * VerticalSliderLineRect, bool movable, UI_Image *window_point) : UI(type, pos, rect, movable)
{
	iPoint position(ViewPortRect->x + ViewPortRect->w + 20, ViewPortRect->y);
	this->text = *text;
	this->slider_type = slider_type;
	if (window!=nullptr) {
		this->window = window_point;
	}
	if (ViewPortRect != nullptr && VerticalSliderLineRect!=nullptr && VerticalSliderBackgroundRect!=nullptr && rect!=nullptr) {
		this->ViewPortRect = *ViewPortRect;
		this->VerticalSliderLineRect = *VerticalSliderLineRect;
		this->VerticalSliderBackgroundRect = *VerticalSliderBackgroundRect;
		this->UI_Rect = *rect;
	}
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

	App->render->DrawQuad(((UI_Slider*)item)->ViewPortRect,White(1), White(1), White(1),255,false,false);
	
	SDL_RenderSetViewport(App->render->renderer, &((UI_Slider*)item)->ViewPortRect);
	for (int i = 0; i < texturestext.Count(); i++) {
		if (slider_type == vertical_slider) {
			App->render->Blit(texturestext[i], 0 - App->render->camera.x, 0 + i * 10 - result*1.1 - App->render->camera.y);
		}
		else {
			App->render->Blit(texturestext[i], 0- result*1.1 - App->render->camera.x, 0 + i * 10 - App->render->camera.y);
		}
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
	if (click == true && slider_type==vertical_slider) {
		itempoint = item->Getpos();
		if (itempoint.y <= ((UI_Slider*)item)->SliderLinePos.y +((UI_Slider*)item)->VerticalSliderLineRect.h - ((UI_Slider*)item)->UI_Rect.h && itempoint.y >= ((UI_Slider*)item)->SliderLinePos.y) {
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

		original_y = itempoint.y;
		item->SetPosition(itempoint.x, itempoint.y);
		UI_Collision.x = itempoint.x;
		UI_Collision.y = itempoint.y;
	}	
	else if (click == true && slider_type == horizontal_slider){
		itempoint = item->Getpos();
		if (itempoint.x <= ((UI_Slider*)item)->SliderLinePos.x + ((UI_Slider*)item)->VerticalSliderLineRect.w - ((UI_Slider*)item)->UI_Rect.w && itempoint.x >= ((UI_Slider*)item)->SliderLinePos.x) {
			int motx, moty;
			App->input->GetMouseMotion(motx, moty);
			if (itempoint.x + motx >((UI_Slider*)item)->SliderLinePos.x + ((UI_Slider*)item)->VerticalSliderLineRect.w - ((UI_Slider*)item)->UI_Rect.w && itempoint.x || itempoint.x + motx < ((UI_Slider*)item)->SliderLinePos.x) {
			}
			else {
				itempoint.x += motx;
			}
		}
		//calc value of slider
		float sliderbutton_x = itempoint.x;
		float sliderbutton_w = ((UI_Slider*)item)->UI_Rect.w;
		float minimumhsliderbarr = ((UI_Slider*)item)->SliderLinePos.x;
		float maximumsliderbarr = ((UI_Slider*)item)->VerticalSliderLineRect.w;
		result = 100 * ((sliderbutton_x - minimumhsliderbarr) / (maximumsliderbarr - sliderbutton_w));
		LOG("Result:%f", result);

		original_y = itempoint.y;
		item->SetPosition(itempoint.x, itempoint.y);
		UI_Collision.x = itempoint.x;
		UI_Collision.y = itempoint.y;
	}
}

void UI_Slider::ModifText(p2SString item)
{
	int texture_w;
	int texture_h;
	char* str = item.GetStringNotConst();
	char *next_token1 = NULL;
	char *seps = "\n";
	token1.PushBack(strtok_s(str, seps, &next_token1));
	if (token1.Count() > 0) {
		while (*next_token1 !='\0')
		{
			token1.PushBack(strtok_s(NULL, seps, &next_token1));
		}
	}
	for (int i = 0; i < token1.Count(); i++) {
		texturestext.PushBack(App->font->Print(token1[i]));
		App->font->CalcSize(token1[i], texture_w, texture_h);
		Text_Tot_H += texture_h;
	}
	incre = (float)Text_Tot_H / 100;
}

void UI_Slider::SetCollision(iPoint * col)
{
	UI_Collision.x = col->x;
	UI_Collision.y = col->y;
}

