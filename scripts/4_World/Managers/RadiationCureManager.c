class RadiationCureItemConfig
{
    string ItemName;
    int CureValuePerSecond;
    int Duration;

    void RadiationCureItemConfig(string itemname, int curevaluepersecond, int duration)
    {
        ItemName = itemname;
        CureValuePerSecond = curevaluepersecond;
        Duration = duration;
    }
}

class RadiationCureManager
{
    private static ref RadiationCureManager s_Instance;
    ref array<ref RadiationCureItemConfig> CureItems;

    void RadiationCureManager()
    {
        CureItems = new array<ref RadiationCureItemConfig>();
    }

    static RadiationCureManager Get()
    {
        if (!s_Instance)
        {
            s_Instance = new RadiationCureManager();
        }
        return s_Instance;
    }

    void LoadCureValues()
    {
        string filePath = "$profile:\\RadiationMod\\";
        string fileName = "RadiationCureItems.json";

        if (FileExist(filePath + fileName))
        {
            JsonFileLoader<array<ref RadiationCureItemConfig>>.JsonLoadFile(filePath + fileName, CureItems);
        }
        else
        {
            CreateDefaultConfig(filePath, fileName);
            JsonFileLoader<array<ref RadiationCureItemConfig>>.JsonLoadFile(filePath + fileName, CureItems);
        }

        LogLoadedCureItems();
    }

    void CreateDefaultConfig(string filePath, string fileName)
    {
        MakeDirectoryPath(filePath);

        CureItems.Insert(new RadiationCureItemConfig("Crackers", 3, 20));
        CureItems.Insert(new RadiationCureItemConfig("RadiationInjection", 5, 15));

        JsonFileLoader<array<ref RadiationCureItemConfig>>.JsonSaveFile(filePath + fileName, CureItems);
    }

    void LogLoadedCureItems()
    {
        foreach (RadiationCureItemConfig item : CureItems)
        {
            Print("[RadiationCureManager] Загружен предмет для вывода радиации \"" + item.ItemName + "\" с эффективностью: " + item.CureValuePerSecond + " в секунду, в течение: " + item.Duration + " секунд");
        }
    }

    void MakeDirectoryPath(string path)
    {
        int lastIndex = path.LastIndexOf("\\");
        string directoriesPath = path.Substring(0, lastIndex + 1);

        if (!FileExist(directoriesPath) && !MakeDirectory(directoriesPath))
        {
            Print("[RadiationCureManager] Failed to create directory: " + directoriesPath);
        }
    }

    RadiationCureItemConfig GetCureItemConfig(string itemName)
    {
        foreach (RadiationCureItemConfig item : CureItems)
        {
            if (item.ItemName == itemName)
            {
                return item;
            }
        }
        return null; 
    }
}
