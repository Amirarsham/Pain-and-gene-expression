# Load required packages
library(ggplot2)
library(dplyr)
library(tidyr)
library(ggsignif)
library(knitr)


# Create a data frame with the data
df <- data.frame(
  Condition = c(rep("Iso.S", 4), rep("Soc.S", 4), rep("Soc.NS", 4), rep("Iso.NS", 4)),
  Replicate = rep(1:4, 4),
  Expression = c(1.57, 0.51, 0.509, 0.341,
                 2.352, 3.574, 1.314, 1.73, 
                 3.045, 2.964, 4.917, 3.733, 
                 1.0001, 1.0002, 1.0003, 1.0004)
)

# Set the baseline as Iso.NS
baseline <- df %>% filter(Condition == "Iso.NS") %>% summarize(Expression = median(Expression))

# Calculate relative expression
df_rel <- df %>% group_by(Condition) %>% mutate(Rel_Exp = Expression / baseline$Expression)

# Perform ANOVA and Tukey's post hoc test
anova <- aov(Rel_Exp ~ Condition, data = df_rel)
posthoc <- TukeyHSD(anova)
# Create table of Tukey HSD post hoc results
posthoc_table <- as.data.frame(posthoc$`Condition`)

# Print table
print(posthoc_table)

# Get summary statistics for ANOVA
summary_anova <- summary(anova)

# Get post hoc test results as a table
posthoc_table <- as.data.frame(TukeyHSD(anova))

# Add column names to posthoc table
colnames(posthoc_table) <- c("Comparison", "Diff_Mean", "Lower_CI", "Upper_CI", "p_value")

# Print the summary statistics for ANOVA and post hoc table
cat("Summary Statistics for ANOVA:\n")
print(summary_anova)

cat("\nPost Hoc Test Table:\n")
print(posthoc_table)


# Perform ANOVA and save the summary
anova <- aov(Rel_Exp ~ Condition, data = df_rel)
anova_summary <- summary(anova)

# Create a data frame with the ANOVA summary
anova_table <- data.frame(
  `Source of Variation` = rownames(anova_summary[[1]]),
  `Sum of Squares` = anova_summary[[1]][,1],
  `Degrees of Freedom` = anova_summary[[1]][,2],
  `Mean Square` = anova_summary[[1]][,3],
  `F Value` = anova_summary[[1]][,4],
  `Pr(>F)` = anova_summary[[1]][,5]
)

# Print the ANOVA table
print(anova_table, row.names = FALSE)


# Plot the box plot with significance lines


ggplot(df_rel, aes(x = Condition, y = Rel_Exp, fill = Condition)) +
  geom_boxplot() + 
  scale_fill_manual(values = c("gray", "lightblue", "blue", "lightgray")) +
  geom_hline(yintercept = 1, linetype = "dashed") +
  labs(x = "Condition", y = "Expression Fold change Relative to IsoNS") +
  theme(axis.text.x = element_text(face = "bold", size = rel(3.1)),axis.title.y = element_text(face = "bold", size = rel(1)),
        panel.grid.major = element_blank(), panel.grid.minor = element_blank())+
  
  ggtitle("Relative Expression of pth2 Gene") +
  geom_signif(comparisons = list(c("Iso.S", "Iso.NS"), c("Soc.NS", "Soc.S"), c("Soc.NS", "Iso.S"), c("Soc.S", "Iso.S")),
              map_signif_level = TRUE, step_increase = 0.07, textsize=4) +
  theme_bw()+
  theme(panel.background = element_rect(fill='transparent'),
    plot.background = element_rect(fill='transparent', color=NA),
    panel.grid.major = element_blank(),
    panel.grid.minor = element_blank(),
    legend.background = element_rect(fill='transparent'),
    legend.box.background = element_rect(fill='transparent'))

# Calculate the median relative expression for each condition
df_rel_summary <- df_rel %>%
  group_by(Condition) %>%
  summarize(median_rel_expression = median(Rel_Exp))

# Print the summary table
kable(df_rel_summary, caption = "Summary of Median Relative Expressions")
# Save the ANOVA table
write.csv(anova_table, "anova_table.csv")
write.csv(df_rel_summary, "df_rel_summary.csv")

# Save the post hoc table
write.csv(posthoc_table, "posthoc_table.csv")

# Pivot the data to create a wide-format table
expression_table <- df %>% 
  pivot_wider(names_from = Replicate, values_from = Expression)

# Add a column for the Condition
expression_table$Condition <- df$Condition

# Save the table as a CSV file
write.csv(expression_table, "expression_table.csv", row.names = FALSE)





