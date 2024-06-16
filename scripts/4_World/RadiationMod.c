class RadiationMod
{
    ref array<ref RadiationTriggerConfig> RadiationTriggers;

    void RadiationMod()
    {
        RadiationTriggers = new array<ref RadiationTriggerConfig>;
        LoadTriggers();
    }

    void LoadTriggers()
    {
        string filePath = "$profile:\\RadiationMod\\";
        string fileName = "RadiationTriggers.json";

        if (FileExist(filePath + fileName))
        {
            JsonFileLoader<RadiationMod>.JsonLoadFile(filePath + fileName, this);
        }
        else
        {
            CreateDefaultConfig(filePath, fileName);
            JsonFileLoader<RadiationMod>.JsonLoadFile(filePath + fileName, this);
        }
    }

    void CreateDefaultConfig(string filePath, string fileName)
    {
        MakeDirectoryPath(filePath);

        RadiationTriggers.Insert(new RadiationTriggerConfig("Тестовый триггер радиации 100 метров", "130 0 1555", "100 20 100", 100));

        JsonFileLoader<RadiationMod>.JsonSaveFile(filePath + fileName, this);
    }

    void MakeDirectoryPath(string path)
    {
        int lastIndex = path.LastIndexOf("\\");
        string directoriesPath = path.Substring(0, lastIndex + 1);

        if (!FileExist(directoriesPath) && !MakeDirectory(directoriesPath))
        {
            Print("[RadiationMod] Failed to create directory: " + directoriesPath);
        }
    }

   void RegisterTriggers()
    {
        foreach (RadiationTriggerConfig config : RadiationTriggers)
        {
            vector min = -config.Size;
            vector max = config.Size;
        
            RadiationTrigger trigger = RadiationTrigger.Cast(GetGame().CreateObject("RadiationTrigger", config.Position, ECE_NONE));
            if (trigger)
            {
                trigger.SetCollisionBox(min, max);
                trigger.SetTriggerName(config.Name);
                trigger.SetRadiationBackground(config.RadiationBackground);

                string triggerInfo = "Установлена зона радиации: \"" + config.Name + "\", Координаты: " + vectorToString(config.Position) + ", Размер: " + vectorToString(config.Size) + ", Радиационный фон: " + config.RadiationBackground;
                Print("[RadiationMod] " + triggerInfo);
            }
        }
    }

    string vectorToString(vector vec)
    {
        return "[" + vec[0] + ", " + vec[1] + ", " + vec[2] + "]";
    }
}
