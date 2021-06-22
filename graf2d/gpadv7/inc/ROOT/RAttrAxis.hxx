/*************************************************************************
 * Copyright (C) 1995-2021, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT7_RAttrAxis
#define ROOT7_RAttrAxis

#include <ROOT/RAttrAggregation.hxx>
#include <ROOT/RAttrLine.hxx>
#include <ROOT/RAttrText.hxx>
#include <ROOT/RAttrValue.hxx>
#include <ROOT/RPadLength.hxx>
#include <cmath>

namespace ROOT {
namespace Experimental {

/** \class RAttrAxis
\ingroup GpadROOT7
\author Sergey Linev <s.linev@gsi.de>
\date 2020-02-20
\brief All supported axes attributes for: line, ticks, labels, title, min/max, log, reverse, ...
\warning This is part of the ROOT 7 prototype! It will change without notice. It might trigger earthquakes. Feedback is welcome!
*/

class RAttrAxis : public RAttrAggregation {

   RAttrValue<double> fMin{this, "min", 0.};                             ///<! axis min
   RAttrValue<double> fMax{this, "max", 0.};                             ///<! axis max
   RAttrValue<double> fZoomMin{this, "zoommin", 0.};                     ///<! axis zoom min
   RAttrValue<double> fZoomMax{this, "zoommax", 0.};                     ///<! axis zoom max
   RAttrValue<double> fLog{this, "log", 0};                              ///<! log scale, <1 off, 1 - base10, 2 - base 2, 2.71 - exp, 3, 4, ...
   RAttrValue<double> fSymlog{this, "symlog", 0};                        ///<! symlog scale constant, 0 - off
   RAttrValue<bool> fReverse{this, "reverse", false};                    ///<! reverse scale
   RAttrValue<bool> fTimeDisplay{this, "time", false};                   ///<! time display
   RAttrValue<double> fTimeOffset{this, "time_offset", 0};               ///<! time offset to display
   RAttrValue<std::string> fTimeFormat{this, "time_format", ""};         ///<! time format
   RAttrLine fAttrLine{this, "line"};                                    ///<! line attributes
   RAttrValue<std::string> fEndingStyle{this, "ending_style", ""};       ///<! axis ending style - none, arrow, circle
   RAttrValue<RPadLength> fEndingSize{this, "ending_size", 0.02_normal}; ///<! axis ending size
   RAttrValue<std::string> fTicksSide{this, "ticks_side", "normal"};     ///<! ticks position - normal, invert, both
   RAttrValue<RPadLength> fTicksSize{this, "ticks_size", 0.02_normal};   ///<! ticks size
   RAttrValue<RColor> fTicksColor{this, "ticks_color", RColor::kBlack};  ///<! ticks color
   RAttrValue<int> fTicksWidth{this, "ticks_width", 1};                  ///<! ticks width
   RAttrValue<bool> fHideLabels{this, "hidelabels", false};              ///<! disable labels drawing
   RAttrText fAttrLabels{this, "labels"};                                ///<! text attributes for labels
   RAttrValue<RPadLength> fLabelsOffset{this, "labels_offset", {}};      ///<! axis labels offset - relative
   RAttrValue<bool> fLabelsCenter{this, "labels_center", false};         ///<! center labels
   RAttrText fAttrTitle{this, "title"};                                  ///<! axis title text attributes
   RAttrValue<std::string> fTitle{this, "title", ""};                    ///<! axis title
   RAttrValue<std::string> fTitlePos{this, "title_position", "right"};   ///<! axis title position - left, right, center
   RAttrValue<RPadLength> fTitleOffset{this, "title_offset", {}};        ///<! axis title offset - relative

   R__ATTR_CLASS(RAttrAxis, "axis");

   RAttrAxis &SetMin(double min) { fMin = min; return *this; }
   RAttrAxis &SetMax(double max) { fMax = max; return *this; }
   double GetMin() const { return fMin; }
   double GetMax() const { return fMax; }
   bool HasMin() const { return fMin.Has(); }
   bool HasMax() const { return fMax.Has(); }

   RAttrAxis &SetMinMax(double min, double max) { SetMin(min); SetMax(max); return *this; }
   void ClearMinMax() { fMin.Clear(); fMax.Clear(); }

   RAttrAxis &SetZoomMin(double min) { fZoomMin = min; return *this; }
   RAttrAxis &SetZoomMax(double max) { fZoomMax = max; return *this; }
   double GetZoomMin() const { return fZoomMin; }
   double GetZoomMax() const { return fZoomMax; }
   bool HasZoomMin() const { return fZoomMin.Has(); }
   bool HasZoomMax() const { return fZoomMax.Has(); }

   RAttrAxis &SetZoom(double min, double max) { SetZoomMin(min); SetZoomMax(max); return *this; }
   void ClearZoom() { fZoomMin.Clear(); fZoomMax.Clear(); }

   RAttrAxis &SetLog(double base = 10) { fLog = (base < 1) ? 0 : base; return *this; }
   double GetLog() const { return fLog; }
   bool IsLogScale() const { return GetLog() > 0.999999; }
   bool IsLog10() const { auto l = GetLog(); return (std::fabs(l-1.) < 1e-6) || (std::fabs(l-10.) < 1e-6); }
   bool IsLog2() const { return std::fabs(GetLog() - 2.) < 1e-6; }
   bool IsLn() const { return std::fabs(GetLog() - 2.71828) < 0.1; }

   RAttrAxis &SetSymlog(double const_value = 0.01)
   {
      if (const_value <= 0.)
         fSymlog.Clear();
      else
         fSymlog = const_value;
      return *this;
   }
   double GetSymlog() const { return fSymlog; }
   bool HasSymlog() const { return fSymlog.Has(); }
   void ClearSymlog() { fSymlog.Clear(); }

   RAttrAxis &SetReverse(bool on = true) { fReverse = on; return *this; }
   bool GetReverse() const { return fReverse; }

   RAttrAxis &SetTimeDisplay(const std::string &fmt = "", double offset = -1)
   {
      fTimeDisplay = true;
      if (!fmt.empty()) fTimeFormat = fmt;
      if (offset >= 0) fTimeOffset = offset;
      return *this;
   }
   bool GetTimeDisplay() const { return fTimeDisplay; }
   void ClearTimeDisplay()
   {
      fTimeDisplay.Clear();
      fTimeOffset.Clear();
      fTimeFormat.Clear();
   }

   const RAttrLine &AttrLine() const { return fAttrLine; }
   RAttrLine &AttrLine() { return fAttrLine; }

   RAttrAxis &SetEndingSize(const RPadLength &sz) { fEndingSize = sz; return *this; }
   RPadLength GetEndingSize() const { return fEndingSize; }

   RAttrAxis &SetEndingStyle(const std::string &st) { fEndingStyle = st; return *this; }
   RAttrAxis &SetEndingArrow() { return SetEndingStyle("arrow"); }
   RAttrAxis &SetEndingCircle() { return SetEndingStyle("cicrle"); }
   std::string GetEndingStyle() const { return fEndingStyle; }

   RAttrAxis &SetTicksSize(const RPadLength &sz) { fTicksSize = sz; return *this; }
   RPadLength GetTicksSize() const { return fTicksSize; }

   RAttrAxis &SetTicksSide(const std::string &side) { fTicksSide = side; return *this; }
   RAttrAxis &SetTicksNormal() { return SetTicksSide("normal"); }
   RAttrAxis &SetTicksInvert() { return SetTicksSide("invert"); }
   RAttrAxis &SetTicksBoth() { return SetTicksSide("both"); }
   std::string GetTicksSide() const { return fTicksSide; }

   RAttrAxis &SetTicksColor(const RColor &color) { fTicksColor = color; return *this; }
   RColor GetTicksColor() const { return fTicksColor; }

   RAttrAxis &SetTicksWidth(int width) { fTicksWidth = width; return *this; }
   int GetTicksWidth() const { return fTicksWidth; }

   RAttrAxis &SetLabelsOffset(const RPadLength &len) { fLabelsOffset = len; return *this; }
   RPadLength GetLabelsOffset() const { return fLabelsOffset; }

   RAttrAxis &SetHideLabels(bool on = true) { fHideLabels = on; return *this; }
   bool GetHideLabels() const { return fHideLabels; }

   const RAttrText &AttrLabels() const { return fAttrLabels; }
   RAttrText &AttrLabels() { return fAttrLabels; }

   RAttrAxis &SetLabelsCenter(bool on = true) { fLabelsCenter = on; return *this; }
   bool GetLabelsCenter() const { return fLabelsCenter; }

   const RAttrText &AttrTitle() const { return fAttrTitle; }
   RAttrText &AttrTitle() { return fAttrTitle; }

   RAttrAxis &SetTitle(const std::string &title) { fTitle = title; return *this; }
   std::string GetTitle() const { return fTitle; }

   RAttrAxis &SetTitlePos(const std::string &pos) { fTitlePos = pos; return *this; }
   RAttrAxis &SetTitleLeft() { return SetTitlePos("left"); }
   RAttrAxis &SetTitleCenter() { return SetTitlePos("center"); }
   RAttrAxis &SetTitleRight() { return SetTitlePos("right"); }
   std::string GetTitlePos() const { return fTitlePos; }

   RAttrAxis &SetTitleOffset(const RPadLength &len) { fTitleOffset = len; return *this; }
   RPadLength GetTitleOffset() const { return fTitleOffset; }
};

} // namespace Experimental
} // namespace ROOT

#endif
