#ifndef SURFACEATTRIBUTES_H
#define SURFACEATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>
#include <ColorAttribute.h>

// ****************************************************************************
// Class: SurfaceAttributes
//
// Purpose:
//    Attributes for the surface plot
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Thu Oct 9 13:31:05 PST 2003
//
// Modifications:
//   
// ****************************************************************************

class SurfaceAttributes : public AttributeSubject
{
public:
    enum ColorByType
    {
        Constant,
        ZValue
    };
    enum Scaling
    {
        Linear,
        Log,
        Skew
    };
    enum LimitsMode
    {
        OriginalData,
        CurrentPlot
    };

    SurfaceAttributes();
    SurfaceAttributes(const SurfaceAttributes &obj);
    virtual ~SurfaceAttributes();

    virtual void operator = (const SurfaceAttributes &obj);
    virtual bool operator == (const SurfaceAttributes &obj) const;
    virtual bool operator != (const SurfaceAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectSurfaceColor();
    void SelectWireframeColor();
    void SelectColorTableName();

    // Property setting methods
    void SetLegendFlag(bool legendFlag_);
    void SetLightingFlag(bool lightingFlag_);
    void SetSurfaceFlag(bool surfaceFlag_);
    void SetWireframeFlag(bool wireframeFlag_);
    void SetLimitsMode(LimitsMode limitsMode_);
    void SetMinFlag(bool minFlag_);
    void SetMaxFlag(bool maxFlag_);
    void SetColorByZFlag(bool colorByZFlag_);
    void SetScaling(Scaling scaling_);
    void SetLineStyle(int lineStyle_);
    void SetLineWidth(int lineWidth_);
    void SetSurfaceColor(const ColorAttribute &surfaceColor_);
    void SetWireframeColor(const ColorAttribute &wireframeColor_);
    void SetSkewFactor(double skewFactor_);
    void SetMin(double min_);
    void SetMax(double max_);
    void SetColorTableName(const std::string &colorTableName_);

    // Property getting methods
    bool                 GetLegendFlag() const;
    bool                 GetLightingFlag() const;
    bool                 GetSurfaceFlag() const;
    bool                 GetWireframeFlag() const;
    LimitsMode           GetLimitsMode() const;
    bool                 GetMinFlag() const;
    bool                 GetMaxFlag() const;
    bool                 GetColorByZFlag() const;
    Scaling              GetScaling() const;
    int                  GetLineStyle() const;
    int                  GetLineWidth() const;
    const ColorAttribute &GetSurfaceColor() const;
          ColorAttribute &GetSurfaceColor();
    const ColorAttribute &GetWireframeColor() const;
          ColorAttribute &GetWireframeColor();
    double               GetSkewFactor() const;
    double               GetMin() const;
    double               GetMax() const;
    const std::string    &GetColorTableName() const;
          std::string    &GetColorTableName();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string ColorByType_ToString(ColorByType);
    static bool ColorByType_FromString(const std::string &, ColorByType &);
protected:
    static std::string ColorByType_ToString(int);
public:
    static std::string Scaling_ToString(Scaling);
    static bool Scaling_FromString(const std::string &, Scaling &);
protected:
    static std::string Scaling_ToString(int);
public:
    static std::string LimitsMode_ToString(LimitsMode);
    static bool LimitsMode_FromString(const std::string &, LimitsMode &);
protected:
    static std::string LimitsMode_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    bool ChangesRequireRecalculation(const SurfaceAttributes &) const;
private:
    bool           legendFlag;
    bool           lightingFlag;
    bool           surfaceFlag;
    bool           wireframeFlag;
    int            limitsMode;
    bool           minFlag;
    bool           maxFlag;
    bool           colorByZFlag;
    int            scaling;
    int            lineStyle;
    int            lineWidth;
    ColorAttribute surfaceColor;
    ColorAttribute wireframeColor;
    double         skewFactor;
    double         min;
    double         max;
    std::string    colorTableName;
};

#endif
