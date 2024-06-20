class RadiationMod
{
    private static ref RadiationMod s_Instance;
    ref array<ref RadiationTriggerConfig> RadiationTriggers;

    void RadiationMod()
    {
        RadiationTriggers = new array<ref RadiationTriggerConfig>;
        LoadTriggers();
    }

    static RadiationMod Get()
    {
        if (!s_Instance)
        {
            s_Instance = new RadiationMod();
        }
        return s_Instance;
    }

    void LoadTriggers()
    {
        string filePath = "$profile:\\RadiationMod\\";
        string fileName = "RadiationTriggers.json";

        if (FileExist(filePath + fileName))
        {
            JsonFileLoader<array<ref RadiationTriggerConfig>>.JsonLoadFile(filePath + fileName, RadiationTriggers);
        }
        else
        {
            CreateDefaultConfig(filePath, fileName);
            JsonFileLoader<array<ref RadiationTriggerConfig>>.JsonLoadFile(filePath + fileName, RadiationTriggers);
        }
    }

    void CreateDefaultConfig(string filePath, string fileName)
    {
        MakeDirectoryPath(filePath);

        RadiationTriggers.Insert(new RadiationTriggerConfig("Тестовый триггер радиации 100", "130 0 1555", "50 50 50", 100));
        RadiationTriggers.Insert(new RadiationTriggerConfig("Тестовый триггер радиации 200", "230 0 1555", "50 50 50", 200));
        RadiationTriggers.Insert(new RadiationTriggerConfig("Тестовый триггер радиации 300", "330 0 1555", "50 50 50", 300));
        RadiationTriggers.Insert(new RadiationTriggerConfig("Тестовый триггер радиации 1000", "430 0 1555", "50 50 50", 1000));
        
        JsonFileLoader<array<ref RadiationTriggerConfig>>.JsonSaveFile(filePath + fileName, RadiationTriggers);
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
