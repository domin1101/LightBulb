// Includes
#include "LightBulbApp/Windows/AbstractWindow.hpp"
#include "LightBulbApp/Windows/AbstractSubApp.hpp"

namespace LightBulb
{
	AbstractWindow::AbstractWindow(AbstractApp& controller_, const std::string& label, AbstractWindow* parent)
		: wxFrame(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize)
	{
		controller = &controller_;
	}

	void AbstractWindow::refreshAfterChange(wxSizer& sizer)
	{
		wxSize clientSize = sizer.ComputeFittingClientSize(this);
		SetMinClientSize(clientSize);
		SetSize(GetSize());
		Layout();
	}
}