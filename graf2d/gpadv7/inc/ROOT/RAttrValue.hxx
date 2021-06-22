/*************************************************************************
 * Copyright (C) 1995-2020, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT7_RAttrValue
#define ROOT7_RAttrValue

#include <ROOT/RAttrBase.hxx>

namespace ROOT {
namespace Experimental {

/** \class RAttrValue
\ingroup GpadROOT7
\author Sergey Linev <s.linev@gsi.de>
\date 2020-06-24
\brief Template class to access single value from drawable or other attributes
\warning This is part of the ROOT 7 prototype! It will change without notice. It might trigger earthquakes. Feedback is welcome!
*/


template<typename T>
class RAttrValue : public RAttrBase {
protected:

   T fDefault;            ///<!    default value

   RAttrMap CollectDefaults() const override
   {
      return RAttrMap().AddValue(GetName(), fDefault);
   }


public:

   RAttrValue() : RAttrBase(""), fDefault() {}

   RAttrValue(RDrawable *drawable, const char *name, const T &dflt = T()) : RAttrBase(drawable, name ? name : ""), fDefault(dflt) { }

   RAttrValue(RAttrBase *parent, const char *name, const T &dflt = T()) : RAttrBase(parent, name ? name : ""), fDefault(dflt) { }

   RAttrValue(const RAttrValue& src) : RAttrBase("")
   {
      Set(src.Get());
      fDefault = src.Default();
   }

   T GetDefault() const { return fDefault; }

   void Set(const T &v)
   {
      if (auto access = EnsureAttr(GetName()))
         access.attr->AddValue(access.fullname, v);
   }

   T Get() const
   {
      if (auto v = AccessValue(GetName(), true))
        return RAttrMap::Value_t::GetValue<T>(v.value);

      return fDefault;
   }

   const char *GetName() const { return GetPrefix(); }

   void Clear() override { ClearValue(GetName()); }

   bool Has() const
   {
      if (auto v = AccessValue(GetName(), true)) {
         auto res = RAttrMap::Value_t::GetValue<const RAttrMap::Value_t *,T>(v.value);
         return res ? (res->Kind() != RAttrMap::kNoValue) : false;
      }

      return false;
   }

   RAttrValue &operator=(const T &v) { Set(v); return *this; }

   RAttrValue &operator=(const RAttrValue &v) { Set(v.Get()); return *this; }

   operator T() const { return Get(); }

   friend bool operator==(const RAttrValue& lhs, const RAttrValue& rhs) { return lhs.Get() == rhs.Get(); }
   friend bool operator!=(const RAttrValue& lhs, const RAttrValue& rhs) { return lhs.Get() != rhs.Get(); }

};

} // namespace Experimental
} // namespace ROOT

#endif // ROOT7_RAttrValue
