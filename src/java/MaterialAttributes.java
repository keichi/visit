package llnl.visit;


// ****************************************************************************
// Class: MaterialAttributes
//
// Purpose:
//    Attributes to control material interface reconstruction
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Tue Aug 16 15:34:56 PST 2005
//
// Modifications:
//   
// ****************************************************************************

public class MaterialAttributes extends AttributeSubject
{
    public MaterialAttributes()
    {
        super(7);

        smoothing = false;
        forceMIR = false;
        cleanZonesOnly = false;
        needValidConnectivity = false;
        useNewMIRAlgorithm = true;
        simplifyHeavilyMixedZones = false;
        maxMaterialsPerZone = 3;
    }

    public MaterialAttributes(MaterialAttributes obj)
    {
        super(7);

        smoothing = obj.smoothing;
        forceMIR = obj.forceMIR;
        cleanZonesOnly = obj.cleanZonesOnly;
        needValidConnectivity = obj.needValidConnectivity;
        useNewMIRAlgorithm = obj.useNewMIRAlgorithm;
        simplifyHeavilyMixedZones = obj.simplifyHeavilyMixedZones;
        maxMaterialsPerZone = obj.maxMaterialsPerZone;

        SelectAll();
    }

    public boolean equals(MaterialAttributes obj)
    {
        // Create the return value
        return ((smoothing == obj.smoothing) &&
                (forceMIR == obj.forceMIR) &&
                (cleanZonesOnly == obj.cleanZonesOnly) &&
                (needValidConnectivity == obj.needValidConnectivity) &&
                (useNewMIRAlgorithm == obj.useNewMIRAlgorithm) &&
                (simplifyHeavilyMixedZones == obj.simplifyHeavilyMixedZones) &&
                (maxMaterialsPerZone == obj.maxMaterialsPerZone));
    }

    // Property setting methods
    public void SetSmoothing(boolean smoothing_)
    {
        smoothing = smoothing_;
        Select(0);
    }

    public void SetForceMIR(boolean forceMIR_)
    {
        forceMIR = forceMIR_;
        Select(1);
    }

    public void SetCleanZonesOnly(boolean cleanZonesOnly_)
    {
        cleanZonesOnly = cleanZonesOnly_;
        Select(2);
    }

    public void SetNeedValidConnectivity(boolean needValidConnectivity_)
    {
        needValidConnectivity = needValidConnectivity_;
        Select(3);
    }

    public void SetUseNewMIRAlgorithm(boolean useNewMIRAlgorithm_)
    {
        useNewMIRAlgorithm = useNewMIRAlgorithm_;
        Select(4);
    }

    public void SetSimplifyHeavilyMixedZones(boolean simplifyHeavilyMixedZones_)
    {
        simplifyHeavilyMixedZones = simplifyHeavilyMixedZones_;
        Select(5);
    }

    public void SetMaxMaterialsPerZone(int maxMaterialsPerZone_)
    {
        maxMaterialsPerZone = maxMaterialsPerZone_;
        Select(6);
    }

    // Property getting methods
    public boolean GetSmoothing() { return smoothing; }
    public boolean GetForceMIR() { return forceMIR; }
    public boolean GetCleanZonesOnly() { return cleanZonesOnly; }
    public boolean GetNeedValidConnectivity() { return needValidConnectivity; }
    public boolean GetUseNewMIRAlgorithm() { return useNewMIRAlgorithm; }
    public boolean GetSimplifyHeavilyMixedZones() { return simplifyHeavilyMixedZones; }
    public int     GetMaxMaterialsPerZone() { return maxMaterialsPerZone; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(smoothing);
        if(WriteSelect(1, buf))
            buf.WriteBool(forceMIR);
        if(WriteSelect(2, buf))
            buf.WriteBool(cleanZonesOnly);
        if(WriteSelect(3, buf))
            buf.WriteBool(needValidConnectivity);
        if(WriteSelect(4, buf))
            buf.WriteBool(useNewMIRAlgorithm);
        if(WriteSelect(5, buf))
            buf.WriteBool(simplifyHeavilyMixedZones);
        if(WriteSelect(6, buf))
            buf.WriteInt(maxMaterialsPerZone);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetSmoothing(buf.ReadBool());
                break;
            case 1:
                SetForceMIR(buf.ReadBool());
                break;
            case 2:
                SetCleanZonesOnly(buf.ReadBool());
                break;
            case 3:
                SetNeedValidConnectivity(buf.ReadBool());
                break;
            case 4:
                SetUseNewMIRAlgorithm(buf.ReadBool());
                break;
            case 5:
                SetSimplifyHeavilyMixedZones(buf.ReadBool());
                break;
            case 6:
                SetMaxMaterialsPerZone(buf.ReadInt());
                break;
            }
        }
    }


    // Attributes
    private boolean smoothing;
    private boolean forceMIR;
    private boolean cleanZonesOnly;
    private boolean needValidConnectivity;
    private boolean useNewMIRAlgorithm;
    private boolean simplifyHeavilyMixedZones;
    private int     maxMaterialsPerZone;
}

