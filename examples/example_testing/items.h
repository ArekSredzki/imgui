
#ifndef ITEMS_H
#define ITEMS_H

#include "imgui.h"
#include <stdio.h> // vsnprintf, sscanf, printf

#include <iostream>
#include <string>
#include <vector>
#include <map>

// TODO:
// refactor each widget into its own class
// parameterize each widget class with attributes that define the contents of the widget
// add widget for the plotting element (protoype using the lines plots in demo)

namespace example
{
  // typdefs
  
  // helpers
  static char* convertStrToChar(const std::string& s);

  // main widgets and widget elements
  static void ShowAppWindow();
  static void ShowMainMenuBar();
  static void ShowMenuFile();
  static void ShowMenuEdit();
  static void ShowMenuView(bool& show_sequence_progress);
  static void ShowMenuAction();
  static void ShowMenuHelp(bool& show_app_about);
  static void SequenceProgressWidget(bool* p_open);
  static void TableWidget(bool* p_open);
  static void TableFilterPopup(const char* popuop_id, ImGuiTextFilter& filter, std::vector<std::string>& column, bool* checked);
  static void FileBrowserWidget(bool* p_open);  
  static void PlotWidget(bool* p_open); 
  static void WorkflowWidget(bool* p_open);

  // static char* convertStrToChar(const std::string& s)
  // { 
  //   int n = s.length();
  //   char char_array[256]; 
  //   strcpy(char_array, s.c_str());
  // }

  static void ShowAppWindow()
  {
    ShowMainMenuBar();
  }

  // Demonstrate creating a fullscreen menu bar and populating it.
  static void ShowMainMenuBar()
  {
    static bool show_app_about = false;
    if (show_app_about)
    {
        ImGui::Begin("About SmartPeak", &show_app_about, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("SmartPeak %s", ImGui::GetVersion()); //TODO: define version function
        ImGui::Separator();
        ImGui::Text("By Douglas McCloskey and contributors.");
        ImGui::Text("SmartPeak is licensed under the MIT License, see LICENSE for more information.");
        ImGui::End();
    }

    static bool show_sequence_progress = false;
    if (show_sequence_progress) SequenceProgressWidget(&show_sequence_progress);

    static bool show_generic_table = true;
    if (show_generic_table) TableWidget(&show_generic_table);
    
    static bool show_file_browser = true;
    if(show_file_browser) FileBrowserWidget(&show_file_browser);
    
    static bool show_plot = true;
    if(show_plot) PlotWidget(&show_plot);
    
    static bool show_workflow = true;
    if(show_workflow) WorkflowWidget(&show_workflow);

    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        ShowMenuFile();
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit"))
      {
        ShowMenuEdit();
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("View"))
      {
        ShowMenuView(show_sequence_progress);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Actions"))
      {
        ShowMenuAction();
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Help"))
      {
        ShowMenuHelp(show_app_about);
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  static void ShowMenuFile()
  {

    ImGui::MenuItem("Main menu", NULL, false, false);
    if (ImGui::MenuItem("New"))
    {
      //TODO: SQL light interface
    }
    if (ImGui::MenuItem("Open...", "Ctrl+O")) 
    {
      //TODO: open file browser modal
    }
    if (ImGui::BeginMenu("Open Recent"))
    {
      //TODO: populate with recent
      ImGui::MenuItem("fish_hat.c");
      ImGui::MenuItem("fish_hat.inl");
      ImGui::MenuItem("fish_hat.h");
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S"))
    {
      //TODO
    }
    if (ImGui::MenuItem("Save As.."))
    {
      //TODO: open save as File browser modal
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Import ..."))
    {
      //TODO
      // sequence, parameters, and all other tables
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Export ..."))
    {
      //TODO
      // sequence, parameters, and all other tables
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
  }

  static void ShowMenuEdit()
  {
    ImGui::MenuItem("Main menu", NULL, false, false);
    if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
    if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
    ImGui::Separator();
    if (ImGui::MenuItem("Cut", "CTRL+X")) {}
    if (ImGui::MenuItem("Copy", "CTRL+C")) {}
    if (ImGui::MenuItem("Paste", "CTRL+V")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Sequence")) {}
    if (ImGui::MenuItem("Transitions")) {}
    if (ImGui::MenuItem("Quant Method")) {}
    if (ImGui::MenuItem("Standards Conc")) {}
    if (ImGui::MenuItem("Comp Filters")) {}
    if (ImGui::MenuItem("Comp Group Filters")) {}
    if (ImGui::MenuItem("Comp QCs")) {}
    if (ImGui::MenuItem("Comp Group QCs")) {}
    if (ImGui::MenuItem("Parameters")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Workflow")) {}
  }

  static void ShowMenuView(bool& show_sequence_progress)
  {
    ImGui::MenuItem("Main menu", NULL, false, false);
    ImGui::MenuItem("Sequence", NULL, &show_sequence_progress);
    if (ImGui::MenuItem("Sequence segments")) {}
    if (ImGui::MenuItem("Sample groups")) {}
    if (ImGui::MenuItem("Workflow wizard")) {}
    if (ImGui::MenuItem("Review plots"))
    {
        if (ImGui::MenuItem("Feature plot")) {}
        if (ImGui::MenuItem("Metric plot")) {}
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Reports"))
    {
        if (ImGui::MenuItem("Feature summary")) {}
        if (ImGui::MenuItem("Sequence summary")) {}
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Log")) {}
  }

  static void ShowMenuAction()
  {
    ImGui::MenuItem("Main menu", NULL, false, false);
    if (ImGui::MenuItem("Run command")) {}
    if (ImGui::MenuItem("Run workflow")) {}
    if (ImGui::MenuItem("Sample groups")) {}
    if (ImGui::MenuItem("Workflow wizard")) {}
    if (ImGui::MenuItem("Quick info"))
    { // TODO: bug
        if (ImGui::MenuItem("Sequence")) {}
        if (ImGui::MenuItem("Transitions")) {}
        if (ImGui::MenuItem("Quant Method")) {}
        if (ImGui::MenuItem("Standards Conc")) {}
        if (ImGui::MenuItem("Comp Filters")) {}
        if (ImGui::MenuItem("Comp Group Filters")) {}
        if (ImGui::MenuItem("Comp QCs")) {}
        if (ImGui::MenuItem("Comp Group QCs")) {}
        if (ImGui::MenuItem("Parameters")) {}
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Integrity checks"))
    {  // TODO: bug
    if (ImGui::MenuItem("Sample consistency")) {}
    if (ImGui::MenuItem("Comp consistency")) {}
    if (ImGui::MenuItem("Comp Group consistency")) {}
    if (ImGui::MenuItem("IS consistency")) {}
    ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Report"))
    {  // TODO: bug
    if (ImGui::MenuItem("Feature summary")) {}
    if (ImGui::MenuItem("Sequence summary")) {}
    ImGui::EndMenu();
    }
  }

  static void ShowMenuHelp(bool& show_app_about)
  {
    ImGui::MenuItem("Main menu", NULL, false, false);
    ImGui::MenuItem("About", NULL, &show_app_about);
    if (ImGui::MenuItem("Documentation")) {}
    if (ImGui::MenuItem("Version")) {}
  }

  /**
   * @brief Displays a sequence progress widget
   * 
   * The purpose of this UI is to allow users to manage the following:
   * - The sample type for each sample
   * - The order of samples in a sequence
   * - The order of sequence segment or sample group execution
   * - The samples included in a given sequence segment or sample group
   * 
   * UI requirements
   * - ability to quickly change views between sample, sequence segment, or
   *    sample group for order and "tag" management
   * - The ability to drag and drop to facilitate re-ordering
   * - The ability to add or remove "tags" (i.e, colored button icons
   *    that symbolize a sample, sequence segment or sample group
   *    categorization)
   * - Filter and sort by sample, sequence segment or sample group
   * - 
   * 
   * 
   */
  static void SequenceProgressWidget(bool* p_open)
  {
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Sequence list", p_open, NULL))
    {
      // left
      
      // TODO: search by sample name (or sample_group or sequence_segment)
      // TODO: switch between samples, sample_groups, and sequence_segments
      // TODO: check for samples included in the "current" analysis
      // TODO: tooltip with status information for each sample
      static int selected = 0;
      ImGui::BeginChild("left pane", ImVec2(150, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
      for (int i = 0; i < 100; ++i)
      {
        // TODO: change to button with color codes for the following
        // - pass = green
        // - warn = yellow
        // - fail = red
        // add progress bar to indicate completed
        char label[128];
        sprintf(label, "MyObject %d", i); // TODO: update for use with sequence list
        if (ImGui::Selectable(label, selected == i))
          selected = i;
      }
      ImGui::EndChild();
      ImGui::SameLine();

      // right

      // TODO add ability to search and filter by
      // - sample_name
      // - sequence_group_name
      // - sample_group_name
      // - sample_type
      // - sample_status (i.e., pass, warn, fail)
      // - completion status
      // TODO change row column to/from sample, sample_group, sequence_group depending on selected in left panel
      ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 line below us
          ImGui::Text("MyObject: %d", selected); //TODO: update for use with sequence list
          ImGui::Separator();

          // TODO: anlaysis output
          ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");

          // TODO: add "tag" dropdown
          // TODO: row of buttons for sequence_group

          // TODO: add "tag" dropdown
          // TODO: row of buttons for sample_group

          // TODO: add "tag" dropdown
          // TODO: drop down for sample type

          // NOTE: each button should have an "x" that deletes the tag
        ImGui::EndChild();
      ImGui::EndGroup();

      // TODO: add selected samples to plot widget
      // TODO: add selected samples to workflow widget
    }
    ImGui::End();
  }  

  static void TableWidget(bool* p_open)
  {
    //TODO: add input for columns and tables (i.e., std::map)
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Generic table", p_open))
    {
      // ImGui::BeginChild("##ScrollingRegion", ImVec2(0, ImGui::GetFontSize() * 20), false, ImGuiWindowFlags_HorizontalScrollbar);

      // table data
      // can we get away with all text based tables?
      const std::vector<std::string> headers = {"Name", "Path"};
      const std::vector<std::string> column0 = {"One", "Two", "Three"};
      const std::vector<std::string> column1 = {"/path/one",  "/path/two",  "/path/three"};
      static bool rows_checked[] = {true, true, true};
      std::vector<std::vector<std::string>> columns;
      columns.push_back(column0);
      columns.push_back(column1);
      
      // static std::vector<bool> column_checked0 = {true, true, true};
      // static std::vector<bool> column_checked1 = {true, true, true};
      // std::vector<std::vector<bool>> columns_checked;
      // columns_checked.push_back(column_checked0);
      // columns_checked.push_back(column_checked1);


      static std::vector<ImGuiTextFilter> filter;
      static ImGuiTextFilter filter0;
      static ImGuiTextFilter filter1;
      filter.push_back(filter0);
      filter.push_back(filter1);

      // headers
      ImGui::Columns(headers.size() + 1, "mycolumns", true);
      ImGui::Separator();
      ImGui::Text("Index");
      ImGui::NextColumn();
      for (int col = 0; col < headers.size(); ++col)
      {
        if (ImGui::Button(headers[col].c_str()))
          ImGui::OpenPopup(&static_cast<char>(col));
        TableFilterPopup(&static_cast<char>(col), filter[col], columns[col], rows_checked);
        ImGui::NextColumn();
      }

      // body
      ImGui::Separator();
      static int selected = -1;
      for (int i = 0; i < columns[0].size(); ++i)
      {
        // check if all columns for the curren row pass the filter
        // bool pass_all_columns = true;
        // for (int j = 0; j < headers.size(); ++j)
        //   if (!filter[j].PassFilter(columns[j][i].c_str()))
        //     pass_all_columns = false;

        bool pass_all_columns = rows_checked[i];
        if (pass_all_columns)
        {
          char label[32];
          sprintf(label, "%d", i);
          if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
              selected = i;
          bool hovered = ImGui::IsItemHovered();
          ImGui::NextColumn();
          for (int j = 0; j < headers.size(); ++j)
          {
            ImGui::Text(columns[j][i].c_str());
            ImGui::NextColumn();
          }
        }
      }
      // ImGui::EndChild();
    }
    ImGui::End();
  }  

  static void TableFilterPopup(const char* popuop_id, ImGuiTextFilter& filter, std::vector<std::string>& column, bool* checked)
  {
    if (ImGui::BeginPopup(popuop_id))
    { 
      // Sorting
      if (ImGui::Button("Asc"))
      {
        //TODO filter ascending
      }
      ImGui::SameLine();
      if (ImGui::Button("Desc"))
      {
        //TODO filter descending
      }

      // Filtering and selecting
      ImGui::Separator();
      filter.Draw();
      // static bool check_all = true;
      if (ImGui::Button("check all"))
        for (int i = 0; i < column.size(); ++i) checked[i] = true;
      ImGui::SameLine();
      if (ImGui::Button("uncheck all"))
        for (int i = 0; i < column.size(); ++i) checked[i] = false;
      for (int i = 0; i < column.size(); ++i)
        if (filter.PassFilter(column[i].c_str()))
          ImGui::Checkbox(column[i].c_str(), &checked[i]);

      // NOTE: Appears to apply the filter immediately
      // // Apply filters
      // ImGui::Separator();
      // if (ImGui::Button("Accept"))
      // {
      //   //TODO: apply filter and exit
      // }
      // ImGui::SameLine();
      // if (ImGui::Button("Cancel"))
      // {
      //   //TODO: exit without applying filter
      // }

      ImGui::EndPopup();
    }
  }  

  // TODO: need to make system and file aware
  // TODO: allow for filtering based on chosen file type
  static void FileBrowserWidget(bool* p_open)
  {

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("File Browser", p_open, NULL))
    {
      typedef char element[256];

      // starting variables
      static char buffilename[256] = "";
      static char bufdirname[256] = "path/to/current/dir";  // TODO: update with current user directory

      // top: up level, current directory string, refresh icon, search
      // ImGui::BeginChild("Top");
      if (ImGui::Button("Up"))
      {
        // TODO: move up one directory
        // TODO: update the list of
      }
      ImGui::SameLine();      
      ImGui::InputText("", bufdirname, 256);
      ImGui::SameLine(); 
      if (ImGui::Button("Refresh"))
      {
        // Refresh right panel and list of files
      }
      ImGui::SameLine();  
      static ImGuiTextFilter filter;
      filter.Draw();
      // ImGui::EndChild();
      ImGui::Separator();

      // left: current directory folders (recursive tree)
      // TODO: develop recursive directory logic
      static int selected_dir = 0;
      ImGui::BeginChild("Directories", ImVec2(120, -ImGui::GetFrameHeightWithSpacing()), true);
      element current_dirs[] = {"dir 1", "dir 2", "dir 3", "dir 4"};
      static int n_current_dirs = 4;
      for (int i = 0; i < n_current_dirs; ++i)
      {
        char label[64];
        sprintf(label, "dir %d", i);
        if (ImGui::Selectable(label, selected_dir == i))
          selected_dir = i;
        if (ImGui::IsItemClicked())
        { 
          // TODO retrieve the path of the system folder...
          sprintf(bufdirname, "%s", current_dirs[i]);  // update the directory name
          // TODO update the table based on what is in the current directory
        }
      }
      ImGui::EndChild();
      ImGui::SameLine();

      // right: files/folders in highlighted directory
      ImGui::BeginChild("Current Directory", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);      
      // headers
      const char* headers[] = {"Name", "Date Modified", "Type", "Size"};
      ImGui::Columns(IM_ARRAYSIZE(headers) + 1, "mycolumns", true); // with border
      ImGui::Separator();      
      ImGui::Text("index");
      ImGui::NextColumn();
      for (int col = 0; col < IM_ARRAYSIZE(headers); ++col)
      {
        ImGui::Text(headers[col]);
        ImGui::NextColumn();
      }
      // Body
      ImGui::Separator();
      // // typedef (todo: change to std::vector/map)
      typedef element row[4];
      row columns[] = { // NOTE: this table can be all char or std::string
        {"file1", "04/15/2018 2:00 PM", ".csv", "1MB"},
        {"file2", "04/15/2018 2:00 PM", ".txt", "2MB"},
        {"file3", "04/15/2018 2:00 PM", ".mzML", "3MB"},
      };
      static int selected_file = -1;
      for (int i = 0; i < IM_ARRAYSIZE(columns); ++i)
      {
        if (filter.PassFilter(columns[i][0]))
        {
          char label[32];
          sprintf(label, "%d", i);
          if (ImGui::Selectable(label, selected_file == i, ImGuiSelectableFlags_SpanAllColumns))
              selected_file = i;
          bool hovered = ImGui::IsItemHovered();
          if (ImGui::IsItemClicked()) // update the selected file
            sprintf(buffilename, "%s", columns[i][0]);
          ImGui::NextColumn();
          for (int j = 0; j < IM_ARRAYSIZE(headers); ++j)
          {
            ImGui::Text(columns[i][j]);
            ImGui::NextColumn();
          }
        }
      }
      ImGui::EndChild();

      // bottom: selected filename, filetypes, open/cancel
      ImGui::BeginGroup();
      // Filtering and selecting
      ImGui::Separator();
      ImGui::Text("File Name:");
      // 
      ImGui::SameLine();
      ImGui::InputText("", buffilename, 256);
      ImGui::SameLine();            
      const char* file_types[] = { ".csv", ".txt", ".mzML", "." };
      if (ImGui::BeginMenu("File Type"))
      {
        for (int i = 0; i < IM_ARRAYSIZE(file_types); ++i)
        {
          ImGui::MenuItem(file_types[i]);
        }
        // ImGui::SameLine(); //TODO: display selected filetype
        // ImGui::Text(file_types[i]);
        ImGui::EndMenu();
      }
      if (ImGui::Button("Accept"))
      {
        // TODO read in the file
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel"))
      {
        // TODO close the modal
      }
      ImGui::EndGroup();
    }
    ImGui::End();
  }  

  // Show plotting widget
  // Provide filters for the following:
  // - sample_name, sequence_group_name, sample_group_name
  // - component_name, component_group_name
  // - sample status: Pass, Warn, Fail
  // Provide a scatter plot with the following
  // - chromatographic points in blue
  // - integrated points in red
  // Bonus:
  // - allows users to click points include/exclude
  //   from the peak

  static void PlotWidget(bool* p_open)
  {
    //TODO: add input for columns and tables (i.e., std::map)
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Generic plot", p_open))
    {
      // typedef (todo: change to std::vector/map)
      typedef char element[256];
      typedef element row[3];
      typedef bool row_checked[3];

      // left: filters
      static int selected_dir = 0;
      char* headers[] = {"sample_name", "sample_type", "component_name"}; // feature or sample columns to filter on
      typedef element row[3];
      row columns[] = {
        {"S1", "A", "C1"},
        {"S1", "A", "C2"},
        {"S2", "A", "C1"},
        {"S2", "A", "C2"},
        {"S3", "B", "C1"},
        {"S3", "B", "C2"},
        {"S4", "B", "C1"},
        {"S4", "B", "C2"},
      };
      typedef bool row_checked[3];
      row_checked columns_checked[] = {
        {true, true, true},
        {true, true, true},
        {true, true, true},
        {true, true, true},
        {true, true, true},
        {true, true, true},
        {true, true, true},
        {true, true, true},
      };
      static ImGuiTextFilter filter[3];
      ImGui::BeginChild("Filters", ImVec2(200, -ImGui::GetFrameHeightWithSpacing()), true);
      for (int j = 0; j < IM_ARRAYSIZE(headers); ++j)
      {
        if (ImGui::Button(headers[j]))
        {
          ImGui::OpenPopup(headers[j]);
        }
        if (ImGui::BeginPopup(headers[j]))
        {
          filter[j].Draw();
          if (ImGui::Button("check all"))
            for (int i = 0; i < IM_ARRAYSIZE(columns); ++i)
              columns_checked[i][j] = true;
          ImGui::SameLine();
          if (ImGui::Button("uncheck all"))
            for (int i = 0; i < IM_ARRAYSIZE(columns); ++i)
              columns_checked[i][j] = false;           
          for (int i = 0; i < IM_ARRAYSIZE(columns); ++i)
          {
            bool pass_other_filters = true;
            for (int k = 0; k < IM_ARRAYSIZE(headers); ++k)
              if (!columns_checked[i][k])
                bool pass_other_filters = false; 
            if (filter[j].PassFilter(columns[i][j]) && pass_other_filters)
              ImGui::Checkbox(columns[i][j], &columns_checked[i][j]);
          }
          ImGui::EndPopup();
        }
        ImGui::Separator();
      }
      ImGui::EndChild();
      ImGui::SameLine();

      // right (Tab 1)
      ImGui::BeginChild("Figure", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
      ImGui::TextWrapped("TODO: add plot");
      ImGui::EndChild();

      // // right (Tab 2)
      // ImGui::BeginChild("Figure", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
      // ImGui::TextWrapped("TODO: add table");
      // ImGui::EndChild();

      // bottom: selectd filename, filetypes, open/cancel
      ImGui::BeginGroup();
      if (ImGui::Button("Download"))
      {
        // TODO download the plot
      }
      ImGui::SameLine();
      if (ImGui::Button("Options"))
      {
        // TODO open a table with the raw data
      }
      ImGui::SameLine();
      if (ImGui::Button("New Tab"))
      {
        // TODO open a table with the raw data
      }
      ImGui::EndGroup();
    }
    ImGui::End();
  } 

  /**
   * TODO: replace with an actual "workflow editor"
   * See ImGui examples of how to do this
   */
  static void WorkflowWidget(bool* p_open)
  {
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Workflow", p_open, NULL))
    {
      // Top
      ImGui::BeginGroup();
      ImGui::Text("Add processing step:");
      ImGui::SameLine();
      const char* sample_ps[] = {"load_mzML"}; // TODO
      if (ImGui::Button("Sample"))
        ImGui::OpenPopup("Sample");          
      if (ImGui::BeginPopup("Sample"))
      { 
        static ImGuiTextFilter sample_filter;
        sample_filter.Draw();
        for (int i = 0; i < IM_ARRAYSIZE(sample_ps); ++i)
        {
          if (sample_filter.PassFilter(sample_ps[i]))
          {
            ImGui::Text(sample_ps[i]);
            if (ImGui::IsItemClicked())
            {
              //TODO:  add table row
            }
          }
        }
        ImGui::EndPopup();
      }
      ImGui::SameLine();
      const char* sequence_segment_ps[] = {"calibrate"}; // TODO
      if (ImGui::Button("Sequence Segment"))
        ImGui::OpenPopup("Sequence Segment");          
      if (ImGui::BeginPopup("Sequence Segment"))
      { 
        static ImGuiTextFilter sequence_segment_filter;
        sequence_segment_filter.Draw();
        for (int i = 0; i < IM_ARRAYSIZE(sequence_segment_ps); ++i)
        {
          if (sequence_segment_filter.PassFilter(sequence_segment_ps[i]))
          {
            ImGui::Text(sequence_segment_ps[i]);
            if (ImGui::IsItemClicked())
            {
              //TODO:  add table row
            }
          }
        }
        ImGui::EndPopup();
      }
      const char* sample_group_ps[] = {"normalize"}; // TODO
      ImGui::SameLine();
      if (ImGui::Button("Sample Group"))
        ImGui::OpenPopup("Sample Group");          
      if (ImGui::BeginPopup("Sample Group"))
      { 
        static ImGuiTextFilter sample_group_filter;
        sample_group_filter.Draw();
        for (int i = 0; i < IM_ARRAYSIZE(sample_group_ps); ++i)
        {
          if (sample_group_filter.PassFilter(sample_group_ps[i]))
          {
            ImGui::Text(sample_group_ps[i]);
            if (ImGui::IsItemClicked())
            {
              //TODO:  add table row
            }
          }
        }
        ImGui::EndPopup();
      }
      ImGui::EndGroup();

      // Middle: 
      // Table Filters
      static std::vector<ImGuiTextFilter> filter;
      static ImGuiTextFilter filter0, filter1, filter2, filter3;
      filter.push_back(filter0); filter.push_back(filter1);
      filter.push_back(filter2); filter.push_back(filter3);

      // Table Data
      const std::vector<std::string> column0 = {"PS1", "PS2", "PS3"};
      const std::vector<std::string> column1 = {"Sample", "SequenceSegment", "Sample"};
      static bool rows_checked[] = {true, true, true};
      static bool rows_enabled[] = {true, true, true};
      std::vector<std::vector<std::string>> columns;
      columns.push_back(column0);
      columns.push_back(column1);

      // Header
      ImGui::BeginChild("Workflow table", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
      const char* headers[] = {"Processing Step", "Processing Type"};
      ImGui::Columns(IM_ARRAYSIZE(headers) + 2, "mycolumns", true);
      ImGui::Text("#");
      ImGui::NextColumn();
      for (int col = 0; col < IM_ARRAYSIZE(headers); ++col)
      {
        if (ImGui::Button(headers[col]))
          ImGui::OpenPopup(headers[col]);
        TableFilterPopup(headers[col], filter[col], columns[col], rows_checked);
        ImGui::NextColumn();
      }
      ImGui::Text("Enabled");
      ImGui::NextColumn();

      // Body
      // TODO: 3 columns with order, process step, checkmark (enabled, disabled)
      ImGui::Separator();
      static int selected = -1;
      for (int i = 0; i < columns[0].size(); ++i)
      {
        if (rows_checked[i])
        {
          char label[32];
          sprintf(label, "%d", i);
          if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
              selected = i;
          bool hovered = ImGui::IsItemHovered();
          ImGui::NextColumn();
          for (int j = 0; j < IM_ARRAYSIZE(headers); ++j)
          {
            ImGui::Text(columns[j][i].c_str());
          // TODO: tooltip description of each processing step
            ImGui::NextColumn();
          }
          ImGui::Checkbox("", &rows_enabled[i]);
          ImGui::NextColumn();
        }
      }
      ImGui::Dummy(ImVec2(0,0));
      ImGui::EndChild();

      // Bottom:
      ImGui::BeginGroup();
      if(ImGui::Button("Run/Resume"))
      {
        // TODO execute the workflow
      }
      ImGui::SameLine();
      if(ImGui::Button("Pause"))
      {
        // TODO pause the workflow
      }
      ImGui::SameLine();
      if(ImGui::Button("Restart"))
      {
        // TODO restart the workflow
      }
      ImGui::EndGroup();

    }
    ImGui::End();
  }  
}
#endif
