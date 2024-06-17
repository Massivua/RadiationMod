class ResistItemConfig
{
     string ItemName;
     int ResistValue;

     void ResistItemConfig(string itemname, int resistvalue)
     {
          ItemName = itemname;
          ResistValue = resistvalue;
     }
};

class ResistManager
{
     private static ref ResistManager s_Instance;
     ref array<ref ResistItemConfig> ResistItems;

     void ResistManager()
     {
          ResistItems = new array<ref ResistItemConfig>();
     }

     static ResistManager Get()
     {
          if (!s_Instance)
          {
               s_Instance = new ResistManager();
          }
          return s_Instance;
     }

     void LoadResistValues()
     {
          string filePath = "$profile:\\RadiationMod\\";
          string fileName = "ResistValues.json";

          if (FileExist(filePath + fileName))
          {
               JsonFileLoader<array<ref ResistItemConfig>>.JsonLoadFile(filePath + fileName, ResistItems);
          }
          else
          {
               CreateDefaultConfig(filePath, fileName);
               JsonFileLoader<array<ref ResistItemConfig>>.JsonLoadFile(filePath + fileName, ResistItems);
          }

          LogLoadedResistItems();
     }

     void CreateDefaultConfig(string filePath, string fileName)
     {
          MakeDirectoryPath(filePath);

          ResistItems.Insert(new ResistItemConfig("GasMask", 20));
          ResistItems.Insert(new ResistItemConfig("NBCGlovesGray", 100));

          JsonFileLoader<array<ref ResistItemConfig>>.JsonSaveFile(filePath + fileName, ResistItems);
    }

     void LogLoadedResistItems()
     {
          array<ref ResistItemConfig> resistItems = ResistItems;
          foreach (ResistItemConfig item : resistItems)
          {
               Print("[ResistManager] Загружен предмет с защитой от радиации \"" + item.ItemName + "\" защита: " + item.ResistValue);
          }
     }

     void MakeDirectoryPath(string path)
     {
          int lastIndex = path.LastIndexOf("\\");
          string directoriesPath = path.Substring(0, lastIndex + 1);

          if (!FileExist(directoriesPath) && !MakeDirectory(directoriesPath))
          {
               Print("[ResistManager] Failed to create directory: " + directoriesPath);
          }
     }

     array<ref ResistItemConfig> GetResistItems()
     {
          return ResistItems;
     }

    float GetTotalResistValue(PlayerBase player)
    {
          float totalResist = 0;
          array<EntityAI> equippedItems = new array<EntityAI>();
          player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, equippedItems);
        
          foreach (EntityAI item : equippedItems)
          {
               string itemType = item.GetType();
            
               foreach (ResistItemConfig resistItem : ResistItems)
               {
                    if (resistItem.ItemName == itemType)
                    {
                         totalResist += resistItem.ResistValue;
                         break;
                    }
               }
          }
          return totalResist;
     }
};

