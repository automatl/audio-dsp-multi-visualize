#ifndef TOMATLLOOKANDFEEL_H_INCLUDED
#define TOMATLLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TomatlLookAndFeel : public LookAndFeel_V3
{
public:
	enum TomatlColorIds
	{
		defaultBackground = 0x2001111,
		defaultText,
		defaultBorder,
		controlBackground,
		activeBackground,
		toggledBackground,
		disabledText
	};

	TomatlLookAndFeel()
	{
		setColour(defaultBackground, Colour::fromString("FF1E1E1E"));
		//setColour(defaultText, Colour::fromString("FF4DC796"));
		setColour(defaultText, Colours::lightgrey);
		setColour(defaultBorder, Colour::fromString("FF535353"));
		setColour(controlBackground, Colour::fromString("FF111111"));
		setColour(activeBackground, findColour(controlBackground).brighter(0.05));
		setColour(toggledBackground, Colours::green);
		setColour(disabledText, Colours::lightgrey);

		setColour(Label::textColourId, findColour(defaultText));
		setColour(ToggleButton::textColourId, findColour(defaultText));
		setColour(TextButton::textColourOffId, findColour(defaultText));
		setColour(TextButton::textColourOnId, findColour(defaultText));
		
		//setColour(Button::)
	}

	virtual void drawTickBox(Graphics& g, Component& c, float x, float y, float w, float h,
		bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
	{
		Image img = ticked ? 
			ImageCache::getFromMemory(BinaryData::check_true_png, BinaryData::check_true_pngSize) : 
			ImageCache::getFromMemory(BinaryData::check_false_png, BinaryData::check_false_pngSize);

		int l = (w - img.getWidth()) / 2;
		int t = (h - img.getHeight());

		g.drawImageAt(img, x + l, y + t);
		
	}

	virtual void drawButtonBackground(Graphics& g, Button& b, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown)
	{
		g.setColour(findColour(defaultBorder));
		g.drawRect(b.getLocalBounds());

		if (isButtonDown)
		{
			g.setColour(findColour(toggledBackground));
		}
		else if (isMouseOverButton)
		{
			g.setColour(findColour(activeBackground));
		}
		else
		{
			g.setColour(findColour(controlBackground));
		}

		g.fillRect(b.getLocalBounds().expanded(-1));
	}

	void drawVerticalSliderHandle(Graphics& g, int x, int y, int w, int h)
	{
		juce::Rectangle<int> area;
		area.setLeft(x - w / 2);
		area.setWidth(w);
		area.setTop(y - h / 2);
		area.setHeight(h);

		g.setColour(findColour(defaultBorder));
		g.fillRect(area);
	}

	virtual void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& s)
	{
		if (style == Slider::SliderStyle::LinearVertical)
		{
			drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
			drawVerticalSliderHandle(g, x + (width - x) / 2, sliderPos, 12, s.isEnabled() ? 8 : 1);
		}
		else if (style == Slider::SliderStyle::TwoValueVertical)
		{
			drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
			drawVerticalSliderHandle(g, x + (width - x) / 2, minSliderPos, 12, s.isEnabled() ? 8 : 1);
			drawVerticalSliderHandle(g, x + (width - x) / 2, maxSliderPos, 12, s.isEnabled() ? 8 : 1);

		}
		else
		{
			LookAndFeel_V3::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
		}
	}

	virtual void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& s)
	{
		if (style == Slider::SliderStyle::LinearVertical || style == Slider::SliderStyle::TwoValueVertical)
		{

			int sliderWidth = 12;

			juce::Rectangle<int> area;
			area.setLeft((width - sliderWidth) / 2);
			area.setTop(y);
			area.setWidth(sliderWidth);
			area.setHeight(height);

			juce::Rectangle<int> selectedArea;
			selectedArea.setLeft(area.getTopLeft().getX());
			selectedArea.setTop(y);
			selectedArea.setWidth(sliderWidth);
			selectedArea.setHeight(sliderPos - y);

			selectedArea.expand(-1, -1);
			
			g.setColour(findColour(controlBackground));
			g.fillRect(area);
			g.setColour(findColour(defaultBorder));
			g.drawRect(area);

			if (selectedArea.getHeight() > 0)
			{
				g.setColour(findColour(activeBackground));
				g.fillRect(selectedArea);
			}
		}
		else
		{
			LookAndFeel_V3::drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
		}
	}

	/*virtual void drawDrawableButton(Graphics& g, DrawableButton& b, bool isMouseOverButton, bool isButtonDown)
	{
		g.setColour(findColour(defaultBorder));
		g.drawRect(b.getLocalBounds());
	}*/
};



#endif  // TOMATLLOOKANDFEEL_H_INCLUDED
